package by.bsuir.servlets;

import by.bsuir.services.AdminService;
import com.kodgemisi.servlet_url_mapping.MappingServlet;
import com.kodgemisi.servlet_url_mapping.ServletUrl;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.SneakyThrows;

@WebServlet(urlPatterns = {"/admin", "/admin/*"})
@MultipartConfig
public class AdminServlet extends MappingServlet {
    private final AdminService adminService = new AdminService();

    public AdminServlet() {
        this.urlMappingRegistrar.
                get("/", this::open).
                post("/addCategory", this::addCategory).
                post("/addProduct", this::addProduct);
    }

    @SneakyThrows
    private void open(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        adminService.getAdminPage(request, response, this);
    }

    @SneakyThrows
    private void addCategory(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        adminService.addCategory(request, response);
    }

    @SneakyThrows
    private void addProduct(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        adminService.addProduct(request, response);
    }
}
