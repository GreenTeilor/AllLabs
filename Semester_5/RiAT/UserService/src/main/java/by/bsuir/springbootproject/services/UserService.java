package by.bsuir.springbootproject.services;

import by.bsuir.springbootproject.dto.OrderDto;
import by.bsuir.springbootproject.dto.UserDto;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;

import java.util.List;

public interface UserService extends BaseService<UserDto>{
    UserDto login (String email, String password);
    List<UserDto> read();
    UserDto getUserById(int id) throws NoResourceFoundException;
    UserDto addAddressAndPhoneNumberInfo(String address, String phoneNumber, Integer userId) throws NoResourceFoundException;

    void createUserOrders(OrderDto orderDto) throws NoResourceFoundException;
}
