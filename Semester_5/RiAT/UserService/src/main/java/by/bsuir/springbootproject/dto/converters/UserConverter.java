package by.bsuir.springbootproject.dto.converters;

import by.bsuir.springbootproject.dto.UserDto;
import by.bsuir.springbootproject.entities.User;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Component
@RequiredArgsConstructor
public class UserConverter implements Converter<UserDto, User> {

    private final OrderConverter orderConverter;

    @Override
    public UserDto toDto(User user) {
        return Optional.ofNullable(user).map(u -> UserDto.builder().
                        id(u.getId()).
                        name(u.getName()).
                        lastName(u.getLastName()).
                        email(u.getEmail()).
                        birthDate(u.getBirthDate()).
                        registrationDate(u.getRegistrationDate()).
                        balance(u.getBalance()).
                        password(u.getPassword()).
                        address(u.getAddress()).
                        phoneNumber(u.getPhoneNumber()).
                        orders(Optional.ofNullable(u.getOrders()).map(orders -> orders.stream().map(orderConverter::toDto).collect(Collectors.toList())).orElse(List.of())).
                        build()).
                orElse(null);
    }

    @Override
    public User fromDto(UserDto userDto) {
        return Optional.ofNullable(userDto).map(u -> User.builder().
                        id(u.getId()).
                        name(u.getName()).
                        lastName(u.getLastName()).
                        email(u.getEmail()).
                        birthDate(u.getBirthDate()).
                        registrationDate(u.getRegistrationDate()).
                        balance(u.getBalance()).
                        password(u.getPassword()).
                        address(u.getAddress()).
                        phoneNumber(u.getPhoneNumber()).
                        orders(Optional.ofNullable(u.getOrders()).map(orders -> orders.stream().map(orderConverter::fromDto).collect(Collectors.toList())).orElse(List.of())).
                        build()).
                orElse(null);
    }
}
