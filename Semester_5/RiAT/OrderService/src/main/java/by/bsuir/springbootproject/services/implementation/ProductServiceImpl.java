package by.bsuir.springbootproject.services.implementation;

import by.bsuir.springbootproject.dto.converters.ProductConverter;
import by.bsuir.springbootproject.dto.CartDto;
import by.bsuir.springbootproject.entities.Product;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.repositories.ProductRepository;
import by.bsuir.springbootproject.services.ProductService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
@RequiredArgsConstructor
@Transactional(readOnly = true)
public class ProductServiceImpl implements ProductService {
    private final ProductRepository productRepository;
    private final ProductConverter productConverter;

    @Override
    public CartDto addProductToCart(int id, CartDto cartDto) throws NoResourceFoundException {
        Product product = productRepository.findById(id).
                orElseThrow(() -> new NoResourceFoundException("No product with id " + id + " found"));
        cartDto.addProduct(productConverter.toDto(product));
        return cartDto;
    }

    @Override
    public CartDto removeProductFromCart(int id, CartDto cartDto) {
        cartDto.removeProduct(id);
        return cartDto;
    }

    @Override
    public CartDto removeAllProductsFromCart(CartDto cartDto) {
        cartDto.clear();
        return cartDto;
    }
}
