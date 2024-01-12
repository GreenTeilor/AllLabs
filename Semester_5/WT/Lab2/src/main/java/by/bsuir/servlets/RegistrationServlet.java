package by.bsuir.servlets;

import by.bsuir.services.RegistrationService;
import com.kodgemisi.servlet_url_mapping.MappingServlet;
import com.kodgemisi.servlet_url_mapping.ServletUrl;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.SneakyThrows;

@WebServlet(urlPatterns = {"/registration"})
public class RegistrationServlet extends MappingServlet {
    private final RegistrationService registrationService = new RegistrationService();

    public RegistrationServlet() {
        this.urlMappingRegistrar.
                get("/", this::open).
                post("/", this::register);
    }

    @SneakyThrows
    private void open(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        registrationService.getRegistrationPage(request, response, this);
    }

    @SneakyThrows
    private void register(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        registrationService.registerUser(request, response, this);
    }
}
