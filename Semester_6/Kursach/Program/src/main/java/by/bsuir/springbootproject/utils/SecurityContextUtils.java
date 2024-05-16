package by.bsuir.springbootproject.utils;

import by.bsuir.springbootproject.entities.User;
import by.bsuir.springbootproject.principal.UserPrincipal;
import org.springframework.security.core.context.SecurityContextHolder;

import java.util.Optional;

public class SecurityContextUtils {
    public static Optional<User> getUser() {
        return SecurityContextHolder.getContext().getAuthentication().getPrincipal()
                instanceof UserPrincipal principal ? Optional.of(principal.getUser()) : Optional.empty();
    }
}
