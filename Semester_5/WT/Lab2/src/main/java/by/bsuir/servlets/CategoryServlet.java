package by.bsuir.servlets;

import by.bsuir.services.CategoryService;
import com.kodgemisi.servlet_url_mapping.MappingServlet;
import com.kodgemisi.servlet_url_mapping.ServletUrl;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.SneakyThrows;

@WebServlet(urlPatterns = {"/categories", "/categories/*"})
public class CategoryServlet extends MappingServlet {
    private final CategoryService categoryService = new CategoryService();

    public CategoryServlet() {
        this.urlMappingRegistrar.
                get("/{name}/paging", this::paging).
                get("/{name}", this::open);
    }

    @SneakyThrows
    private void open(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        String category = servletUrl.variable("name");
        categoryService.getCategoryProducts(request, response, this, category);
    }

    @SneakyThrows
    private void paging(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        String category = servletUrl.variable("name");
        categoryService.paging(request, response, this, category);
    }
}