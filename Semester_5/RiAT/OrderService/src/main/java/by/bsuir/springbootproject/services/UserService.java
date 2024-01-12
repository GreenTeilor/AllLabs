package by.bsuir.springbootproject.services;

import by.bsuir.springbootproject.dto.CartDto;
import by.bsuir.springbootproject.dto.OrderDto;
import by.bsuir.springbootproject.dto.UserDto;
import by.bsuir.springbootproject.exceptions.InsufficientFundsException;
import by.bsuir.springbootproject.exceptions.NoProductsInOrderException;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;

public interface UserService {
    UserDto getUserById(int id) throws NoResourceFoundException;
    OrderDto makeOrder(UserDto userDto, CartDto cartDto) throws InsufficientFundsException, NoProductsInOrderException;
}
