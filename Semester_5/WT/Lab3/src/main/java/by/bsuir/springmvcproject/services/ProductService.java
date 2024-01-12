package by.bsuir.springmvcproject.services;

import by.bsuir.springmvcproject.entities.Cart;
import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.entities.Product;
import by.bsuir.springmvcproject.entities.SearchCriteria;
import by.bsuir.springmvcproject.exceptions.NoResourceFoundException;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.IOException;
import java.math.BigDecimal;

public interface ProductService extends BaseService<Product>{
    ModelAndView getCategoryProducts(String category, PagingParams params);
    ModelAndView getProductById(int id) throws NoResourceFoundException;
    ModelAndView findProducts(SearchCriteria searchCriteria);
    ModelAndView addProductToCart(int id, Cart cart) throws NoResourceFoundException;
    ModelAndView changeFilter(SearchCriteria searchCriteria, String categoryName, BigDecimal priceFrom, BigDecimal priceTo);
    ModelAndView saveProduct(Product product, String category, MultipartFile image) throws IOException;
}
