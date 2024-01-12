package by.bsuir.springbootproject.dto;

import jakarta.validation.constraints.NotNull;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class CartDto {
    @NotNull(message = "List of products in cart is empty")
    private final List<ProductDto> products = new ArrayList<>();

    public void addProduct(ProductDto product) {
        if (!products.contains(product))
            products.add(product);
    }

    public void removeProduct(int id) {
        Optional<ProductDto> product = products.stream().filter(p -> p.getId() == id).findFirst();
        product.ifPresent(products::remove);
    }

    public BigDecimal getPrice() {
        return products.stream().reduce(BigDecimal.ZERO, (p1, p2) -> p1.add(p2.getPrice()), BigDecimal::add);
    }

    public boolean isEmpty() {
        return products.isEmpty();
    }

    public int size() {
        return products.size();
    }

    public List<ProductDto> getProducts() {
        return products;
    }

    public void clear() {
        products.clear();
    }
}
