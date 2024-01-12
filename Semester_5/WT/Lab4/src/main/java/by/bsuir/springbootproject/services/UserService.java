package by.bsuir.springbootproject.services;

import by.bsuir.springbootproject.entities.Cart;
import by.bsuir.springbootproject.entities.PagingParams;
import by.bsuir.springbootproject.entities.Statistics;
import by.bsuir.springbootproject.entities.User;
import by.bsuir.springbootproject.exceptions.InsufficientFundsException;
import by.bsuir.springbootproject.exceptions.NoProductsInOrderException;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import org.springframework.validation.BindingResult;
import org.springframework.web.servlet.ModelAndView;

import java.util.Optional;

public interface UserService extends BaseService<User>{
    ModelAndView processLoginPage(String error);
    Optional<User> getUserByEmail(String email);
    ModelAndView getUserInfo(User user, PagingParams params);
    ModelAndView addAddressAndPhoneNumberInfo(String address, String phoneNumber, User userInSession, BindingResult bindingResult, PagingParams params);
    Statistics getUserStatistics(int id);
    ModelAndView makeOrder(User user, Cart cart) throws InsufficientFundsException, NoProductsInOrderException, NoResourceFoundException;
}
