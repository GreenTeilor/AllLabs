package by.bsuir.springbootproject.services;

import by.bsuir.springbootproject.dto.CartDto;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;

public interface ProductService {
    CartDto addProductToCart(int id, CartDto cartDto) throws NoResourceFoundException;
    CartDto removeProductFromCart(int id, CartDto cartDto);
    CartDto removeAllProductsFromCart(CartDto cartDto);
}
