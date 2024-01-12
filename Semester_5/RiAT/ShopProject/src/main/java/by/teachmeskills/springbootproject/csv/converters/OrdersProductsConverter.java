package by.teachmeskills.springbootproject.csv.converters;

import by.teachmeskills.springbootproject.csv.OrderProductCsv;
import by.teachmeskills.springbootproject.csv.ProductCsv;
import by.teachmeskills.springbootproject.entities.Order;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicReference;

@Component
@RequiredArgsConstructor
public class OrdersProductsConverter {

    private final ProductConverter productConverter;

    public List<Order> toOrders(List<OrderProductCsv> ordersProductsDto) {
        Map<Integer, Order> orders = new HashMap<>();
        if (ordersProductsDto != null) {
            ordersProductsDto.forEach(orderProduct -> {
                Integer orderId = orderProduct.getOrderId();
                if (!orders.containsKey(orderId)) {
                    orders.put(orderId, Order.
                            builder().
                            date(orderProduct.getOrderDate()).
                            userId(orderProduct.getUserId()).
                            products(new ArrayList<>()).
                            price(orderProduct.getPrice()).
                            build());
                }
                orders.get(orderId).getProducts().add(productConverter.fromCsv(ProductCsv.
                        builder().
                        id(orderProduct.getId()).
                        name(orderProduct.getName()).
                        description(orderProduct.getDescription()).
                        imagePath(orderProduct.getImagePath()).
                        categoryName(orderProduct.getCategoryName()).
                        price(orderProduct.getPrice()).
                        build()));
            });
            return orders.values().stream().toList();
        }
        return null;
    }

    public List<OrderProductCsv> fromOrders(List<Order> ordersDto) {
        List<OrderProductCsv> ordersProducts = new ArrayList<>();
        AtomicReference<Integer> i = new AtomicReference<>(0);
        if (ordersDto != null) {
            ordersDto.forEach(orderDto -> {
                orderDto.getProducts().stream().map(productConverter::toCsv).forEach(productCsv -> ordersProducts.add(OrderProductCsv.
                        builder().
                        id(productCsv.getId()).
                        name(productCsv.getName()).
                        description(productCsv.getDescription()).
                        imagePath(productCsv.getImagePath()).
                        categoryName(productCsv.getCategoryName()).
                        orderDate(orderDto.getDate()).
                        userId(orderDto.getUserId()).
                        orderId(i.get()).
                        price(productCsv.getPrice()).
                        build()));
                i.set(i.get() + 1);
            });
            return ordersProducts;
        }
        return null;
    }
}