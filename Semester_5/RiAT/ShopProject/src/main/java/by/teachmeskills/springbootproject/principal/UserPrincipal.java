package by.teachmeskills.springbootproject.principal;

import by.teachmeskills.springbootproject.entities.Role;
import by.teachmeskills.springbootproject.entities.User;
import org.springframework.security.core.authority.SimpleGrantedAuthority;


public class UserPrincipal extends org.springframework.security.core.userdetails.User {
    private final User user;

    public UserPrincipal(User user) {
        super(user.getEmail(), user.getPassword(), user.getRoles().stream().map(Role::getName).map(SimpleGrantedAuthority::new).toList());
        this.user = user;
    }

    public User getUser() {
        return user;
    }
}
