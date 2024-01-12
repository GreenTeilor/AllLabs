package by.bsuir.servlets;

import by.bsuir.services.ProductService;
import com.kodgemisi.servlet_url_mapping.MappingServlet;
import com.kodgemisi.servlet_url_mapping.ServletUrl;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.SneakyThrows;

@WebServlet(urlPatterns = {"/products/*"})
public class ProductServlet extends MappingServlet {
    private final ProductService productService = new ProductService();

    public ProductServlet() {
        this.urlMappingRegistrar.
                get("/{id}", this::open);
    }

    @SneakyThrows
    private void open(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        String id = servletUrl.variable("id");
        productService.getProduct(request, response, this, id);
    }
}
