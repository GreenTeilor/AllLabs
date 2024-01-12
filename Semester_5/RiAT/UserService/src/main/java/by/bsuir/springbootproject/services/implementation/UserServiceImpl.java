package by.bsuir.springbootproject.services.implementation;

import at.favre.lib.crypto.bcrypt.BCrypt;
import by.bsuir.springbootproject.dto.OrderDto;
import by.bsuir.springbootproject.dto.UserDto;
import by.bsuir.springbootproject.dto.converters.OrderConverter;
import by.bsuir.springbootproject.dto.converters.UserConverter;
import by.bsuir.springbootproject.entities.User;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.exceptions.UserAlreadyExistsException;
import by.bsuir.springbootproject.repositories.UserRepository;
import by.bsuir.springbootproject.services.UserService;
import lombok.RequiredArgsConstructor;
import org.apache.kafka.common.errors.AuthorizationException;
import org.springframework.kafka.annotation.EnableKafka;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

@Service
@EnableKafka
@RequiredArgsConstructor
@Transactional(readOnly = true)
public class UserServiceImpl implements UserService {
    private final UserRepository userRepository;
    private final UserConverter userConverter;
    private final OrderConverter orderConverter;

    @Override
    public UserDto login(String email, String password) {
        Optional<User> user = userRepository.findByEmail(email);
        if (user.isPresent() && BCrypt.verifyer().verify(password.toCharArray(), user.get().getPassword()).verified) {
            return userConverter.toDto(user.get());
        } else {
           throw new AuthorizationException("No user with such creds found");
        }
    }

    @Override
    public UserDto getUserById(int id) throws NoResourceFoundException {
        return userRepository.findById(id).map(userConverter::toDto).orElseThrow(() ->
                new NoResourceFoundException("No user with id " + id + " found"));
    }

    @Override
    @Transactional
    public UserDto addAddressAndPhoneNumberInfo(String address, String phoneNumber, Integer userId) throws NoResourceFoundException {
        User user = userRepository.findById(userId).orElseThrow(() ->
                new NoResourceFoundException("No user with id " + userId + " found"));
        user.setAddress(address);
        user.setPhoneNumber(phoneNumber);
        user = userRepository.save(user);
        return userConverter.toDto(user);
    }

    @Override
    @Transactional
    public UserDto create(UserDto user) throws UserAlreadyExistsException {
        user.setBalance(BigDecimal.valueOf(0.0));
        user.setRegistrationDate(LocalDate.now());
        user.setPassword(BCrypt.withDefaults().hashToString(12, user.getPassword().toCharArray()));
        if (userRepository.findByEmail(user.getEmail()).isPresent()) {
            throw new UserAlreadyExistsException("User already exists");
        }
        return userConverter.toDto(userRepository.save(userConverter.fromDto(user)));
    }

    @Override
    public List<UserDto> read() {
        return userRepository.findAll().stream().map(userConverter::toDto).toList();
    }

    @Override
    @Transactional
    public UserDto update(UserDto user) throws NoResourceFoundException {
        userRepository.findById(user.getId()).orElseThrow(() ->
                new NoResourceFoundException("No user with id " + user.getId() + " found"));
        return userConverter.toDto(userRepository.save(userConverter.fromDto(user)));
    }

    @Override
    @Transactional
    public void delete(int id) {
        userRepository.deleteById(id);
    }


    @Override
    @KafkaListener(topics = {"${topic.user-order-topic}"})
    @Transactional
    public void createUserOrders(OrderDto orderDto) throws NoResourceFoundException {
        User user = userRepository.findById(orderDto.getUserId()).orElseThrow(() ->
                new NoResourceFoundException("No user with id " + orderDto.getUserId() + " found"));
        user.setBalance(user.getBalance().subtract(orderDto.getPrice()));
        user.getOrders().add(orderConverter.fromDto(orderDto));
        userRepository.save(user);
    }
}
