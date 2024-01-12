package by.bsuir.springmvcproject.repositories.impl;

import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.entities.User;
import by.bsuir.springmvcproject.repositories.UserRepository;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import lombok.RequiredArgsConstructor;
import org.hibernate.Session;
import org.hibernate.query.MutationQuery;
import org.hibernate.query.NativeQuery;
import org.hibernate.query.Query;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
@RequiredArgsConstructor
public class UserRepositoryImpl implements UserRepository {
    private final static String GET_USER_BY_EMAIL = "select u from User u where u.email=:email";
    private final static String SEARCH_USER_QUERY = "select u from User u where u.email=:email and u.password=:password";
    private final static String UPDATE_ADDRESS_AND_PHONE_NUMBER_QUERY = "update User set address=:address, phoneNumber=:phoneNumber where email=:email";
    private final static String GET_ALL_USERS_QUERY = "select u from User u";
    private final static String GET_USER_FAVORITE_GENRE = "SELECT category FROM (SELECT category, count(*) as count " +
            "FROM orders_products JOIN products ON productId = products.id " +
            "JOIN orders ON orderId = orders.id WHERE userId = ? GROUP BY category) as res1 ORDER BY count DESC LIMIT 1";

    private final static String GET_USER_DAYS_REGISTERED = "SELECT datediff(CURRENT_TIMESTAMP, registrationDate) as result FROM users WHERE id = ?";
    private final static String GET_USER_PURCHASED_BOOKS_COUNT = "SELECT count(*) FROM orders_products JOIN orders ON orderId = orders.id WHERE userId = ?";
    private final static String GET_USER_ORDERS_COUNT = "SELECT count(*) FROM orders WHERE userId = ?";

    @PersistenceContext
    private final EntityManager manager;

    @Override
    public Optional<User> getUserByEmail(String email) {
        Session session = manager.unwrap(Session.class);
        Query<User> query = session.createQuery(GET_USER_BY_EMAIL, User.class);
        query.setParameter("email", email);
        return Optional.ofNullable(query.uniqueResult());
    }

    @Override
    public Optional<User> getUserById(int id) {
        Session session = manager.unwrap(Session.class);
        return Optional.ofNullable(session.get(User.class, id));
    }

    @Override
    public User getUser(String email, String password) {
        Session session = manager.unwrap(Session.class);
        Query<User> query = session.createQuery(SEARCH_USER_QUERY, User.class);
        query.setParameter("email", email);
        query.setParameter("password", password);
        return query.uniqueResult();
    }

    @Override
    public void updateAddressAndPhoneNumber(String address, String phoneNumber, String email) {
        Session session = manager.unwrap(Session.class);
        MutationQuery query = session.createMutationQuery(UPDATE_ADDRESS_AND_PHONE_NUMBER_QUERY);
        query.setParameter("address", address);
        query.setParameter("phoneNumber", phoneNumber);
        query.setParameter("email", email);
        query.executeUpdate();
    }

    @Override
    public String getUserFavoriteCategory(int id) {
        Session session = manager.unwrap(Session.class);
        NativeQuery<String> query = session.createNativeQuery(GET_USER_FAVORITE_GENRE, String.class);
        query.setParameter(1, id);
        String result = query.getSingleResultOrNull();
        return result != null ? result : "Не определен";
    }

    @Override
    public int getUserDaysRegistered(int id) {
        Session session = manager.unwrap(Session.class);
        NativeQuery<Integer> query = session.createNativeQuery(GET_USER_DAYS_REGISTERED, Integer.class);
        query.setParameter(1, id);
        return query.getSingleResult();
    }

    @Override
    public int getUserPurchasedBooksCount(int id) {
        Session session = manager.unwrap(Session.class);
        NativeQuery<Integer> query = session.createNativeQuery(GET_USER_PURCHASED_BOOKS_COUNT, Integer.class);
        query.setParameter(1, id);
        return query.getSingleResult();
    }

    @Override
    public int getUserOrdersCount(int id) {
        Session session = manager.unwrap(Session.class);
        NativeQuery<Integer> query = session.createNativeQuery(GET_USER_ORDERS_COUNT, Integer.class);
        query.setParameter(1, id);
        return query.getSingleResult();
    }

    @Override
    public User create(User user) {
        Session session = manager.unwrap(Session.class);
        user.setPassword(user.getPassword());
        session.persist(user);
        return user;
    }

    @Override
    public List<User> read(PagingParams params) {
        Session session = manager.unwrap(Session.class);
        Query<User> query = session.createQuery(GET_ALL_USERS_QUERY, User.class);
        query.setFirstResult((params.getPageNumber() - 1) * params.getPageSize());
        query.setMaxResults(params.getPageSize());
        return query.getResultList();
    }

    @Override
    public User update(User user) {
        Session session = manager.unwrap(Session.class);
        return session.merge(user);
    }

    @Override
    public void delete(int id) {
        Session session = manager.unwrap(Session.class);
        User user = session.get(User.class, id);
        session.remove(user);
    }
}
