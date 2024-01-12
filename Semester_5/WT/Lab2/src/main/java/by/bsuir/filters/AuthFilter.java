package by.bsuir.filters;

import by.bsuir.constants.SessionAttributesNames;
import by.bsuir.domain.User;
import jakarta.servlet.Filter;
import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.ServletRequest;
import jakarta.servlet.ServletResponse;
import jakarta.servlet.annotation.WebFilter;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.Paths;
import java.util.Collections;
import java.util.List;

@WebFilter("/*")
public class AuthFilter implements Filter {
    private final static String LOGIN_URI = "/login";

    @Override
    public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain) throws ServletException, IOException {
        HttpServletRequest request = (HttpServletRequest) req;
        HttpServletResponse response = (HttpServletResponse) res;
        String URI = request.getRequestURI();
        String contextPath = request.getContextPath();
        if (
                auth(List.of("/profile/**", "/profile"), URI, request, Collections.emptyList()) &&
                auth(List.of("/admin/**", "/admin"), URI, request, List.of("ROLE_ADMIN")) &&
                auth(List.of("/cart/makeOrder"), URI, request, Collections.emptyList())
        ) {
            chain.doFilter(request, response);
        } else {
            response.sendRedirect(contextPath + LOGIN_URI);
        }
    }

    private boolean auth(List<String> protectedURIS, String actualURI, HttpServletRequest request, List<String> requiredRoles) {
        for (String URI : protectedURIS) {
            if (isPathMatches(actualURI, request.getContextPath() + URI)) {
                HttpSession session = request.getSession();
                User user = (User) session.getAttribute(SessionAttributesNames.USER);
                if (user != null) {
                    boolean isAuthorized = true;
                    for (String role : requiredRoles) {
                        isAuthorized &= user.hasRole(role);
                    }
                    return isAuthorized;
                }
                return false;
            }
        }
        return true;
    }

    public boolean isPathMatches(String path, String template) {
        return FileSystems.getDefault()
                .getPathMatcher("glob:" + template)
                .matches(Paths.get(path));
    }
}
