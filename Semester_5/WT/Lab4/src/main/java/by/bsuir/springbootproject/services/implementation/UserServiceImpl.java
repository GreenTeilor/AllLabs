package by.bsuir.springbootproject.services.implementation;

import by.bsuir.springbootproject.constants.PagesPaths;
import by.bsuir.springbootproject.constants.RequestAttributesNames;
import by.bsuir.springbootproject.entities.Cart;
import by.bsuir.springbootproject.entities.Order;
import by.bsuir.springbootproject.entities.PagingParams;
import by.bsuir.springbootproject.entities.Statistics;
import by.bsuir.springbootproject.entities.User;
import by.bsuir.springbootproject.exceptions.InsufficientFundsException;
import by.bsuir.springbootproject.exceptions.NoProductsInOrderException;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.exceptions.UserAlreadyExistsException;
import by.bsuir.springbootproject.repositories.OrderRepository;
import by.bsuir.springbootproject.repositories.UserRepository;
import by.bsuir.springbootproject.services.UserService;
import by.bsuir.springbootproject.utils.ErrorPopulatorUtils;
import lombok.RequiredArgsConstructor;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
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
        return userRepository.findByEmail(email);
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
        Pageable paging = PageRequest.of(params.getPageNumber(), params.getPageSize(), Sort.by("date").descending());
        List<Order> orders = orderRepository.findAllByUserId(user.getId(), paging);
        Statistics statistics = getUserStatistics(user.getId());
        return makeModelAndView(user, statistics, orders);
    }

    @Override
    @Transactional
    public ModelAndView addAddressAndPhoneNumberInfo(String address, String phoneNumber, User user, BindingResult bindingResult, PagingParams params) {
        Statistics statistics = getUserStatistics(user.getId());
        Pageable paging = PageRequest.of(params.getPageNumber(), params.getPageSize(), Sort.by("date").descending());
        List<Order> orders = orderRepository.findAllByUserId(user.getId(), paging);
        if (!bindingResult.hasFieldErrors(RequestAttributesNames.ADDRESS) && !bindingResult.hasFieldErrors(RequestAttributesNames.PHONE_NUMBER)) {
            user.setAddress(address);
            user.setPhoneNumber(phoneNumber);
            userRepository.save(user);
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
        if (userRepository.findById(user.getId()).map(User::getBalance).
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
        userRepository.save(user);
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
        userRepository.save(user);
        modelAndView.addObject(RequestAttributesNames.STATUS, "Успешно");
        modelAndView.addObject(RequestAttributesNames.COLOR, "green");
        return modelAndView;
    }

    @Override
    public ModelAndView read(PagingParams params) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.HOME_PAGE);
        Pageable paging = PageRequest.of(params.getPageNumber(), params.getPageSize(), Sort.by("name").ascending());
        modelAndView.addObject(RequestAttributesNames.USER, userRepository.findAll(paging).getContent());
        return modelAndView;
    }

    @Override
    @Transactional
    public User update(User user) throws NoResourceFoundException {
        userRepository.findById(user.getId()).orElseThrow(() ->
                new NoResourceFoundException("No user with id " + user.getId() + " found"));
        return userRepository.save(user);
    }

    @Override
    @Transactional
    public void delete(int id) {
        userRepository.deleteById(id);
    }
}
