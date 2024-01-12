package by.bsuir.springmvcproject.repositories;

import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.entities.User;

import java.util.List;
import java.util.Optional;

public interface UserRepository {
    User create(User entity);

    List<User> read(PagingParams params);

    User update(User entity);

    void delete(int id);
    Optional<User> getUserByEmail(String email);

    Optional<User> getUserById(int id);

    User getUser(String email, String password);

    void updateAddressAndPhoneNumber(String address, String phoneNumber, String email);

    String getUserFavoriteCategory(int id);
    int getUserDaysRegistered(int id);
    int getUserPurchasedBooksCount(int id);
    int getUserOrdersCount(int id);
}
