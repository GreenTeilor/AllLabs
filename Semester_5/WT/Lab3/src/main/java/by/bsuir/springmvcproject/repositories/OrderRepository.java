package by.bsuir.springmvcproject.repositories;

import by.bsuir.springmvcproject.entities.Order;
import by.bsuir.springmvcproject.entities.PagingParams;

import java.util.List;

public interface OrderRepository {
    Order create(Order entity);

    List<Order> read();

    Order update(Order entity);

    void delete(int id);

    List<Order> findAllByUserId(int userId, PagingParams params);
}
