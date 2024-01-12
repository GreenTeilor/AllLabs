package by.bsuir.servlets;

import by.bsuir.services.LoginService;
import com.kodgemisi.servlet_url_mapping.MappingServlet;
import com.kodgemisi.servlet_url_mapping.ServletUrl;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.SneakyThrows;

@WebServlet(urlPatterns = {"/login"})
public class LoginServlet extends MappingServlet {
    private final LoginService loginService = new LoginService();

    public LoginServlet() {
        this.urlMappingRegistrar.
                get("/", this::open).
                post("/", this::login);
    }

    @SneakyThrows
    private void open(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        loginService.getLoginPage(request, response, this);
    }

    @SneakyThrows
    private void login(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        loginService.login(request, response, this);
    }
}
