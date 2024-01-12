package by.bsuir.springbootproject.repositories;

import by.bsuir.springbootproject.entities.Order;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface OrderRepository extends JpaRepository<Order, Integer> {
    List<Order> findAllByUserId(Integer id, Pageable paging);
    List<Order> findAllByUserId(Integer id);
}
