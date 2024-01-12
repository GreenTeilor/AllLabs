package by.bsuir.servlets;

import by.bsuir.services.ProfileService;
import com.kodgemisi.servlet_url_mapping.MappingServlet;
import com.kodgemisi.servlet_url_mapping.ServletUrl;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.SneakyThrows;

@WebServlet(urlPatterns = {"/profile", "/profile/*"})
public class ProfileServlet extends MappingServlet {
    private final ProfileService profileService = new ProfileService();

    public ProfileServlet() {
        this.urlMappingRegistrar.
                get("/", this::open).
                get("/paging", this::paging).
                post("/", this::addAddressAndPhoneNumber);
    }

    @SneakyThrows
    private void open(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        profileService.getUserInfo(request, response, this);
    }

    @SneakyThrows
    private void paging(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        profileService.paging(request, response, this);
    }

    @SneakyThrows
    private void addAddressAndPhoneNumber(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        profileService.addAddressAndPhoneNumber(request, response);
    }
}
