package by.bsuir.springmvcproject.controllers;

import by.bsuir.springmvcproject.constants.RequestAttributesNames;
import by.bsuir.springmvcproject.constants.SessionAttributesNames;
import by.bsuir.springmvcproject.constants.Values;
import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.services.ProductService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("/categories")
@SessionAttributes(SessionAttributesNames.PRODUCT_PAGING_PARAMS)
@RequiredArgsConstructor
public class CategoryController {
    private final ProductService productService;

    @GetMapping("/{categoryName}")
    public ModelAndView openCategory(@PathVariable String categoryName,
                                     @ModelAttribute(SessionAttributesNames.PRODUCT_PAGING_PARAMS) PagingParams params) {
        ModelAndView modelAndView = productService.getCategoryProducts(categoryName, params);
        modelAndView.addObject(RequestAttributesNames.CATEGORY_NAME, categoryName);
        return modelAndView;
    }

    @GetMapping("/{categoryName}/paging")
    public ModelAndView changePagingParams(@PathVariable String categoryName,
                                      @ModelAttribute(SessionAttributesNames.PRODUCT_PAGING_PARAMS) PagingParams params) {
        return productService.getCategoryProducts(categoryName, params);
    }

    @ModelAttribute(SessionAttributesNames.PRODUCT_PAGING_PARAMS)
    public PagingParams initializePagingParams() {
        return new PagingParams(Values.DEFAULT_START_PAGE, Values.DEFAULT_PAGE_SIZE);
    }
}
