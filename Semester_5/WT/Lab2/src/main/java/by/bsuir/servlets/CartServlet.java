package by.bsuir.servlets;

import by.bsuir.services.CartService;
import com.kodgemisi.servlet_url_mapping.MappingServlet;
import com.kodgemisi.servlet_url_mapping.ServletUrl;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.SneakyThrows;

@WebServlet(urlPatterns = {"/cart", "/cart/*"})
public class CartServlet extends MappingServlet {
    private final CartService cartService = new CartService();

    public CartServlet() {
        this.urlMappingRegistrar.
                get("/", this::open).
                get("/addProduct/{id}", this::addProduct).
                get("/removeProduct/{id}", this::removeProduct).
                get("/clear", this::clear).
                get("/makeOrder", this::makeOrder);
    }

    @SneakyThrows
    private void open(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        cartService.getCart(request, response, this);
    }

    @SneakyThrows
    private void addProduct(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        String id = servletUrl.variable("id");
        cartService.addProduct(request, response, id);
    }

    @SneakyThrows
    private void removeProduct(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        String id = servletUrl.variable("id");
        cartService.removeProduct(request, response, this, id);
    }

    @SneakyThrows
    private void clear(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        cartService.clearCart(request, response, this);
    }

    @SneakyThrows
    private void makeOrder(HttpServletRequest request, HttpServletResponse response, ServletUrl servletUrl) {
        cartService.makeOrder(request, response, this);
    }
}
