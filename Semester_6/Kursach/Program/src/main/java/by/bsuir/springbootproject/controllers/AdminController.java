package by.bsuir.springbootproject.controllers;

import by.bsuir.springbootproject.constants.PagesPaths;
import by.bsuir.springbootproject.constants.RequestAttributesNames;
import by.bsuir.springbootproject.entities.Category;
import by.bsuir.springbootproject.entities.PagingParams;
import by.bsuir.springbootproject.entities.Product;
import by.bsuir.springbootproject.services.CategoryService;
import by.bsuir.springbootproject.services.ProductService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.IOException;
import java.math.BigDecimal;

@Controller
@RequestMapping("/admin")
@RequiredArgsConstructor
public class AdminController {

    private final CategoryService categoryService;
    private final ProductService productService;

    @GetMapping
    public ModelAndView openAdminPage() {
        ModelAndView modelAndView = categoryService.read(new PagingParams(0, 1000_000_000));
        modelAndView.setViewName(PagesPaths.ADMIN_PAGE);
        return modelAndView;
    }

    @PostMapping("/addCategory")
    public ModelAndView addCategory(@RequestParam(RequestAttributesNames.CATEGORY_NAME) String name,
                                    @RequestParam(RequestAttributesNames.CATEGORY_FILE) MultipartFile file)
            throws IOException {
        return categoryService.saveCategory(Category.builder().
                name(name).
                build(), file);
    }

    @PostMapping("addProduct")
    public ModelAndView addProduct(@RequestParam(RequestAttributesNames.PRODUCT_NAME) String name,
                                   @RequestParam(RequestAttributesNames.PRODUCT_DESCRIPTION) String description,
                                   @RequestParam(RequestAttributesNames.PRODUCT_CATEGORY) String category,
                                   @RequestParam(RequestAttributesNames.PRODUCT_PRICE) String price,
                                   @RequestParam(RequestAttributesNames.PRODUCT_FILE) MultipartFile file)
            throws IOException {
        return productService.saveProduct(Product.builder().
                name(name).
                description(description).
                price(new BigDecimal(price)).
                build(), category, file);
    }
}
