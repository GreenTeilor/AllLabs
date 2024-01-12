package by.teachmeskills.springbootproject.repositories;

import by.teachmeskills.springbootproject.entities.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.Optional;

public interface UserRepository extends JpaRepository<User, Integer> {
    Optional<User> findByEmail(String email);

    Optional<User> findByEmailAndPassword(String email, String password);

    @Query(value = "SELECT category FROM (SELECT category, count(*) as count " +
            "FROM orders_products JOIN products ON productId = products.id " +
            "JOIN orders ON orderId = orders.id WHERE userId = ? GROUP BY category) as res1 ORDER BY count DESC LIMIT 1", nativeQuery = true)
    String getUserFavoriteCategory(int id);

    @Query(value = "SELECT datediff(CURRENT_TIMESTAMP, registrationDate) as result FROM users WHERE id = ?", nativeQuery = true)
    int getUserDaysRegistered(int id);

    @Query(value = "SELECT count(*) FROM orders_products JOIN orders ON orderId = orders.id WHERE userId = ?", nativeQuery = true)
    int getUserPurchasedBooksCount(int id);

    @Query(value = "SELECT count(*) FROM orders WHERE userId = ?", nativeQuery = true)
    int getUserOrdersCount(int id);
}
