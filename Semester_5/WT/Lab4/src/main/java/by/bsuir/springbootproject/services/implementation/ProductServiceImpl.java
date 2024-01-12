package by.bsuir.springbootproject.services.implementation;

import by.bsuir.springbootproject.constants.PagesPaths;
import by.bsuir.springbootproject.constants.RequestAttributesNames;
import by.bsuir.springbootproject.constants.Values;
import by.bsuir.springbootproject.entities.Cart;
import by.bsuir.springbootproject.entities.PagingParams;
import by.bsuir.springbootproject.entities.Product;
import by.bsuir.springbootproject.entities.SearchCriteria;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.repositories.CategoryRepository;
import by.bsuir.springbootproject.repositories.ProductRepository;
import by.bsuir.springbootproject.repositories.ProductSearchSpecification;
import by.bsuir.springbootproject.services.ProductService;
import lombok.RequiredArgsConstructor;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.File;
import java.io.IOException;
import java.math.BigDecimal;
import java.util.List;

@Service
@RequiredArgsConstructor
@Transactional(readOnly = true)
public class ProductServiceImpl implements ProductService {
    private final ProductRepository productRepository;
    private final CategoryRepository categoryRepository;

    @Override
    public ModelAndView getCategoryProducts(String category, PagingParams params) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.CATEGORY_PAGE);
        Pageable paging = PageRequest.of(params.getPageNumber(), params.getPageSize(), Sort.by("name").ascending());
        List<Product> products = productRepository.findAllByCategory_Name(category, paging);
        modelAndView.addObject(RequestAttributesNames.CATEGORY_PRODUCTS, products);
        modelAndView.addObject(RequestAttributesNames.CATEGORY_NAME, category);
        return modelAndView;
    }

    @Override
    public ModelAndView getProductById(int id) throws NoResourceFoundException {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.PRODUCT_PAGE);
        Product product = productRepository.findById(id).
                orElseThrow(() -> new NoResourceFoundException("Product with id " + id + " not found"));
        modelAndView.addObject(product.getName());
        modelAndView.addObject(product);
        return modelAndView;
    }

    @Override
    public ModelAndView findProducts(SearchCriteria searchCriteria) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.SEARCH_PAGE);
        if (searchCriteria.getPageNumber() < 0) {
            searchCriteria.setPageNumber(Values.DEFAULT_START_PAGE);
        }
        Pageable paging = PageRequest.of(searchCriteria.getPageNumber(), searchCriteria.getPageSize(), Sort.by("name").ascending());
        Specification<Product> specification = new ProductSearchSpecification(searchCriteria);
        modelAndView.addObject(RequestAttributesNames.PRODUCTS, productRepository.findAll(specification, paging).getContent());
        modelAndView.addObject(RequestAttributesNames.CATEGORIES, categoryRepository.findAll());
        return modelAndView;
    }

    @Override
    public ModelAndView addProductToCart(int id, Cart cart) throws NoResourceFoundException {
        ModelAndView modelAndView = new ModelAndView("redirect:/products/" + id);
        Product product = productRepository.findById(id).
                orElseThrow(() -> new NoResourceFoundException("No product with id " + id + " found"));
        cart.addProduct(product);
        return modelAndView;
    }

    @Override
    public ModelAndView changeFilter(SearchCriteria searchCriteria, String categoryName, BigDecimal priceFrom, BigDecimal priceTo) {
        searchCriteria.setKeyWords("");
        searchCriteria.setSearchCategory(categoryName);
        searchCriteria.setPriceFrom(priceFrom);
        searchCriteria.setPriceTo(priceTo);
        searchCriteria.setPageNumber(Values.DEFAULT_START_PAGE);
        return findProducts(searchCriteria);
    }

    @Override
    @Transactional
    public ModelAndView saveProduct(Product product, String category, MultipartFile image) throws IOException {
        String fileName = image.getOriginalFilename();
        image.transferTo(new File("src\\main\\webapp\\assets\\" + fileName));
        product.setCategory(categoryRepository.findByName(category).orElse(null));
        product.setImagePath("assets/" + fileName);
        productRepository.save(product);
        return new ModelAndView("redirect:/admin");
    }

    @Override
    @Transactional
    public ModelAndView create(Product product) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.PRODUCT_PAGE);
        productRepository.save(product);
        return modelAndView;
    }

    @Override
    public ModelAndView read(PagingParams params) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.SEARCH_PAGE);
        Pageable paging = PageRequest.of(params.getPageNumber(), params.getPageSize(), Sort.by("name").ascending());
        modelAndView.addObject(RequestAttributesNames.PRODUCTS, productRepository.findAll(paging).getContent());
        modelAndView.addObject(RequestAttributesNames.CATEGORIES, categoryRepository.findAll());
        return modelAndView;
    }

    @Override
    @Transactional
    public Product update(Product product) throws NoResourceFoundException {
        productRepository.findById(product.getId()).orElseThrow(() ->
                new NoResourceFoundException("No product with id " + product.getId() + " found"));
        return productRepository.save(product);
    }

    @Override
    @Transactional
    public void delete(int id) {
        productRepository.deleteById(id);
    }
}
