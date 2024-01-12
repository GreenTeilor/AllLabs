package by.bsuir.springbootproject.services.implementation;

import by.bsuir.springbootproject.dto.OrderDto;
import by.bsuir.springbootproject.dto.UserDto;
import by.bsuir.springbootproject.dto.converters.OrderConverter;
import by.bsuir.springbootproject.dto.converters.ProductConverter;
import by.bsuir.springbootproject.dto.converters.UserConverter;
import by.bsuir.springbootproject.dto.CartDto;
import by.bsuir.springbootproject.entities.Order;
import by.bsuir.springbootproject.exceptions.InsufficientFundsException;
import by.bsuir.springbootproject.exceptions.NoProductsInOrderException;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.repositories.UserRepository;
import by.bsuir.springbootproject.services.UserService;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.ArrayList;

@Service
@RequiredArgsConstructor
@Transactional(readOnly = true)
public class UserServiceImpl implements UserService {
    private final UserRepository userRepository;
    private final UserConverter userConverter;
    private final OrderConverter orderConverter;
    private final ProductConverter productConverter;
    private final KafkaTemplate<String, OrderDto> kafkaOrderDtoTemplate;

    @Value("${topic.user-order-topic}")
    private String userOrderTopic;

    @Override
    public UserDto getUserById(int id) throws NoResourceFoundException {
        return userRepository.findById(id).map(userConverter::toDto).orElseThrow(() ->
                new NoResourceFoundException("No user with id " + id + " found"));
    }

    @Override
    @Transactional
    public OrderDto makeOrder(UserDto userDto, CartDto cartDto) throws InsufficientFundsException, NoProductsInOrderException {
        BigDecimal orderPrice = cartDto.getPrice();
        if (userDto.getBalance().compareTo(orderPrice) < 0) {
            throw new InsufficientFundsException("Insufficient funds");
        }
        if (cartDto.isEmpty()) {
            throw new NoProductsInOrderException("Cart is empty");
        }
        Order order = Order.builder().userId(userDto.getId()).date(LocalDate.now()).products(
                new ArrayList<>(cartDto.getProducts().stream().map(productConverter::fromDto).toList())).price(orderPrice).build();
        OrderDto orderDto = orderConverter.toDto(order);
        kafkaOrderDtoTemplate.send(userOrderTopic, String.valueOf(orderDto.hashCode()), orderDto);
        kafkaOrderDtoTemplate.flush();
        return orderDto;
    }
}
