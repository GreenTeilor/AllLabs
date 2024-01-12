package by.bsuir.springmvcproject.utils;

import by.bsuir.springmvcproject.entities.User;
import by.bsuir.springmvcproject.principal.UserPrincipal;
import org.springframework.security.core.context.SecurityContextHolder;

import java.util.Optional;

public class SecurityContextUtils {
    public static Optional<User> getUser() {
        return SecurityContextHolder.getContext().getAuthentication().getPrincipal()
                instanceof UserPrincipal principal ? Optional.of(principal.getUser()) : Optional.empty();
    }
}
