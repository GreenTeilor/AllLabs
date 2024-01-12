package by.teachmeskills.springbootproject.utils;

import by.teachmeskills.springbootproject.entities.User;
import by.teachmeskills.springbootproject.principal.UserPrincipal;
import org.springframework.security.core.context.SecurityContextHolder;

import java.util.Optional;

public class SecurityContextUtils {
    public static Optional<User> getUser() {
        return SecurityContextHolder.getContext().getAuthentication().getPrincipal()
                instanceof UserPrincipal principal ? Optional.of(principal.getUser()) : Optional.empty();
    }
}
