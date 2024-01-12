package by.bsuir.springmvcproject.principal;

import by.bsuir.springmvcproject.entities.Role;
import by.bsuir.springmvcproject.entities.User;
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
