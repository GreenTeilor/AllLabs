package by.bsuir.springmvcproject.services;

import by.bsuir.springmvcproject.entities.Cart;
import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.entities.Statistics;
import by.bsuir.springmvcproject.entities.User;
import by.bsuir.springmvcproject.exceptions.InsufficientFundsException;
import by.bsuir.springmvcproject.exceptions.NoProductsInOrderException;
import by.bsuir.springmvcproject.exceptions.NoResourceFoundException;
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
