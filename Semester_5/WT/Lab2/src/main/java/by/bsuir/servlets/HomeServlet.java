package by.bsuir.servlets;

import by.bsuir.services.HomeService;
import com.kodgemisi.servlet_url_mapping.MappingServlet;
import com.kodgemisi.servlet_url_mapping.ServletUrl;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import lombok.SneakyThrows;

@WebServlet(urlPatterns = {"/home", "/home/*"})
public class HomeServlet extends MappingServlet {
    private final HomeService homeService = new HomeService();

    public HomeServlet() {
        this.urlMappingRegistrar.
                get("/", this::open).
                get("/paging", this::paging).
                get("/logout", this::logout);
    }

    @SneakyThrows
    private void open(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        homeService.getHomePage(request, response, this);
    }

    @SneakyThrows
    private void paging(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        homeService.paging(request, response, this);
    }

    @SneakyThrows
    private void logout(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        homeService.logout(request, response);
    }
}
