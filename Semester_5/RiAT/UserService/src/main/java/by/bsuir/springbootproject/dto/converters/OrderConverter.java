package by.bsuir.springbootproject.dto.converters;

import by.bsuir.springbootproject.dto.OrderDto;
import by.bsuir.springbootproject.entities.Order;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.Optional;

@Component
@RequiredArgsConstructor
public class OrderConverter implements Converter<OrderDto, Order> {

    private final ProductConverter productConverter;

    @Override
    public OrderDto toDto(Order order) {
        return Optional.ofNullable(order).map(o -> OrderDto.builder().
                        id(o.getId()).
                        date(o.getDate()).
                        products(Optional.ofNullable(o.getProducts()).map(products -> products.stream().map(productConverter::toDto).toList()).orElse(List.of())).
                        userId(o.getUserId()).
                        price(o.getPrice()).
                        build()).
                orElse(null);
    }

    @Override
    public Order fromDto(OrderDto orderDto) {
        return Optional.ofNullable(orderDto).map(o -> Order.builder().
                        id(o.getId()).
                        date(o.getDate()).
                        products(Optional.ofNullable(o.getProducts()).map(products -> products.stream().map(productConverter::fromDto).toList()).orElse(List.of())).
                        userId(o.getUserId()).
                        price(o.getPrice()).
                        build()).
                orElse(null);
    }
}
