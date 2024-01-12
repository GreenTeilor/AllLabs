package by.teachmeskills.springbootproject.services.implementation;

import by.teachmeskills.springbootproject.constants.PagesPaths;
import by.teachmeskills.springbootproject.constants.RequestAttributesNames;
import by.teachmeskills.springbootproject.constants.Values;
import by.teachmeskills.springbootproject.csv.ProductCsv;
import by.teachmeskills.springbootproject.csv.converters.ProductConverter;
import by.teachmeskills.springbootproject.entities.Cart;
import by.teachmeskills.springbootproject.entities.PagingParams;
import by.teachmeskills.springbootproject.entities.Product;
import by.teachmeskills.springbootproject.entities.SearchCriteria;
import by.teachmeskills.springbootproject.exceptions.NoResourceFoundException;
import by.teachmeskills.springbootproject.repositories.CategoryRepository;
import by.teachmeskills.springbootproject.repositories.ProductRepository;
import by.teachmeskills.springbootproject.repositories.ProductSearchSpecification;
import by.teachmeskills.springbootproject.services.ProductService;
import com.opencsv.CSVWriter;
import com.opencsv.bean.CsvToBean;
import com.opencsv.bean.CsvToBeanBuilder;
import com.opencsv.bean.StatefulBeanToCsv;
import com.opencsv.bean.StatefulBeanToCsvBuilder;
import com.opencsv.exceptions.CsvDataTypeMismatchException;
import com.opencsv.exceptions.CsvRequiredFieldEmptyException;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

@Service
@RequiredArgsConstructor
@Transactional(readOnly = true)
public class ProductServiceImpl implements ProductService {
    private final ProductRepository productRepository;
    private final CategoryRepository categoryRepository;
    private final ProductConverter productConverter;

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
    public void saveToFile(String categoryName, HttpServletResponse response) throws IOException, CsvRequiredFieldEmptyException, CsvDataTypeMismatchException {
        try (Writer writer = new OutputStreamWriter(response.getOutputStream())) {
            StatefulBeanToCsv<ProductCsv> beanToCsv = new StatefulBeanToCsvBuilder<ProductCsv>(writer)
                    .withQuotechar(CSVWriter.NO_QUOTE_CHARACTER)
                    .withSeparator('~')
                    .build();
            response.setContentType("text/csv");
            response.setHeader("Content-Disposition", "attachment; filename=" + "products.csv");
            List<Product> products = productRepository.findAllByCategory_Name(categoryName);
            products.forEach(p -> p.setId(null));
            beanToCsv.write(products.stream().map(productConverter::toCsv).toList());
        }
    }

    @Override
    @Transactional
    public ModelAndView loadFromFile(String categoryName, MultipartFile file) throws IOException {
        ModelAndView modelAndView = new ModelAndView("redirect:/categories/" + categoryName);
        try (Reader reader = new BufferedReader(new InputStreamReader(file.getInputStream()))) {
            CsvToBean<ProductCsv> csvToBean = new CsvToBeanBuilder<ProductCsv>(reader)
                    .withType(ProductCsv.class)
                    .withIgnoreLeadingWhiteSpace(true)
                    .withSeparator('~')
                    .build();
            List<ProductCsv> products = new ArrayList<>();
            csvToBean.forEach(products::add);
            products.stream().map(productConverter::fromCsv).forEach(productRepository::save);
            return modelAndView;
        }
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
