package by.bsuir.springmvcproject.repositories.impl;

import by.bsuir.springmvcproject.entities.Order;
import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.repositories.OrderRepository;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import lombok.RequiredArgsConstructor;
import org.hibernate.Session;
import org.hibernate.query.Query;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
@RequiredArgsConstructor
public class OrderRepositoryImpl implements OrderRepository {
    private final static String GET_ALL_ORDERS_QUERY = "select o from Order o";
    private final static String GET_USER_ORDERS_QUERY = "select o from Order o where o.userId=:userId";

    @PersistenceContext
    private final EntityManager manager;

    @Override
    public Order create(Order order) {
        Session session = manager.unwrap(Session.class);
        session.persist(order);
        return order;
    }

    @Override
    public List<Order> read() {
        Session session = manager.unwrap(Session.class);
        return session.createQuery(GET_ALL_ORDERS_QUERY, Order.class).getResultList();
    }

    @Override
    public Order update(Order order) {
        Session session = manager.unwrap(Session.class);
        return session.merge(order);
    }

    @Override
    public void delete(int id) {
        Session session = manager.unwrap(Session.class);
        Order order = session.get(Order.class, id);
        session.remove(order);
    }

    @Override
    public List<Order> findAllByUserId(int userId, PagingParams params) {
        Session session = manager.unwrap(Session.class);
        Query<Order> query = session.createQuery(GET_USER_ORDERS_QUERY, Order.class);
        query.setParameter("userId", userId);
        query.setFirstResult((params.getPageNumber() - 1) * params.getPageSize());
        query.setMaxResults(params.getPageSize());
        return query.getResultList();
    }
}
