package by.bsuir.springmvcproject.services.impl;

import by.bsuir.springmvcproject.constants.PagesPaths;
import by.bsuir.springmvcproject.constants.RequestAttributesNames;
import by.bsuir.springmvcproject.entities.Cart;
import by.bsuir.springmvcproject.entities.Order;
import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.entities.Statistics;
import by.bsuir.springmvcproject.entities.User;
import by.bsuir.springmvcproject.exceptions.InsufficientFundsException;
import by.bsuir.springmvcproject.exceptions.NoProductsInOrderException;
import by.bsuir.springmvcproject.exceptions.NoResourceFoundException;
import by.bsuir.springmvcproject.exceptions.UserAlreadyExistsException;
import by.bsuir.springmvcproject.repositories.OrderRepository;
import by.bsuir.springmvcproject.repositories.UserRepository;
import by.bsuir.springmvcproject.services.UserService;
import by.bsuir.springmvcproject.utils.ErrorPopulatorUtils;
import lombok.RequiredArgsConstructor;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.validation.BindingResult;
import org.springframework.web.servlet.ModelAndView;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
@Transactional(readOnly = true)
public class UserServiceImpl implements UserService {
    private final UserRepository userRepository;
    private final OrderRepository orderRepository;
    private final PasswordEncoder encoder;

    @Override
    public ModelAndView processLoginPage(String error) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.LOGIN_PAGE);
        if (error != null) {
            modelAndView.addObject("status", "Неверный логин или пароль");
        }
        return modelAndView;
    }

    @Override
    public Optional<User> getUserByEmail(String email) {
        return userRepository.getUserByEmail(email);
    }

    public static ModelAndView makeModelAndView(User user, Statistics statistics, List<Order> orders) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.PROFILE_PAGE);
        modelAndView.addObject(RequestAttributesNames.USER, user);
        modelAndView.addObject(RequestAttributesNames.STATISTICS, statistics);
        modelAndView.addObject(RequestAttributesNames.ORDERS, orders);
        return modelAndView;
    }

    @Override
    public ModelAndView getUserInfo(User user, PagingParams params) {
        List<Order> orders = orderRepository.findAllByUserId(user.getId(), params);
        Statistics statistics = getUserStatistics(user.getId());
        return makeModelAndView(user, statistics, orders);
    }

    @Override
    @Transactional
    public ModelAndView addAddressAndPhoneNumberInfo(String address, String phoneNumber, User user, BindingResult bindingResult, PagingParams params) {
        Statistics statistics = getUserStatistics(user.getId());
        List<Order> orders = orderRepository.findAllByUserId(user.getId(), params);
        if (!bindingResult.hasFieldErrors(RequestAttributesNames.ADDRESS) && !bindingResult.hasFieldErrors(RequestAttributesNames.PHONE_NUMBER)) {
            user.setAddress(address);
            user.setPhoneNumber(phoneNumber);
            userRepository.update(user);
        }
        ModelAndView modelAndView = makeModelAndView(user, statistics, orders);
        ErrorPopulatorUtils.populateError(RequestAttributesNames.ADDRESS, modelAndView, bindingResult);
        ErrorPopulatorUtils.populateError(RequestAttributesNames.PHONE_NUMBER, modelAndView, bindingResult);
        return modelAndView;
    }

    @Override
    public Statistics getUserStatistics(int id) {
        String favoriteCategory = userRepository.getUserFavoriteCategory(id);
        return Statistics.builder().userId(id).daysRegistered(userRepository.getUserDaysRegistered(id)).
                orderCount(userRepository.getUserOrdersCount(id)).
                booksCount(userRepository.getUserPurchasedBooksCount(id)).
                favoriteCategory(favoriteCategory == null ? "Неизвестен" : favoriteCategory).build();
    }

    @Override
    @Transactional
    public ModelAndView makeOrder(User user, Cart cart) throws InsufficientFundsException, NoProductsInOrderException, NoResourceFoundException {
        BigDecimal orderPrice = cart.getPrice();
        if (userRepository.getUserById(user.getId()).map(User::getBalance).
                orElseThrow(() -> new NoResourceFoundException("No user with id " + user.getId() + " found")).
                compareTo(orderPrice) < 0) {
            throw new InsufficientFundsException("Недостаточно средств");
        }
        if (cart.isEmpty()) {
            throw new NoProductsInOrderException("Корзина пуста");
        }
        Order order = Order.builder().userId(user.getId()).date(LocalDate.now()).products(new ArrayList<>(cart.getProducts())).price(orderPrice).build();
        user.getOrders().add(order);
        user.setBalance(user.getBalance().subtract(orderPrice));
        userRepository.update(user);
        cart.clear();
        ModelAndView modelAndView = new ModelAndView(PagesPaths.CART_PAGE);
        modelAndView.addObject(RequestAttributesNames.STATUS, "Заказ оформлен!");
        modelAndView.addObject(RequestAttributesNames.COLOR, "green");
        return modelAndView;
    }

    @Override
    @Transactional
    public ModelAndView create(User user) throws UserAlreadyExistsException {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.REGISTER_PAGE);
        user.setBalance(BigDecimal.valueOf(0.0));
        user.setRegistrationDate(LocalDate.now());
        user.setPassword(encoder.encode(user.getPassword()));
        if (getUserByEmail(user.getEmail()).isPresent()) {
            throw new UserAlreadyExistsException("Такой пользователь уже существует");
        }
        userRepository.create(user);
        modelAndView.addObject(RequestAttributesNames.STATUS, "Успешно");
        modelAndView.addObject(RequestAttributesNames.COLOR, "green");
        return modelAndView;
    }

    @Override
    public ModelAndView read(PagingParams params) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.HOME_PAGE);
        modelAndView.addObject(RequestAttributesNames.USER, userRepository.read(params));
        return modelAndView;
    }

    @Override
    @Transactional
    public User update(User user) throws NoResourceFoundException {
        userRepository.getUserById(user.getId()).orElseThrow(() ->
                new NoResourceFoundException("No user with id " + user.getId() + " found"));
        return userRepository.update(user);
    }

    @Override
    @Transactional
    public void delete(int id) {
        userRepository.delete(id);
    }
}
