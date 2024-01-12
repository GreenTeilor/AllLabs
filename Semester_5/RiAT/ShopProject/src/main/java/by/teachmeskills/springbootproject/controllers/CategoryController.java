package by.teachmeskills.springbootproject.controllers;

import by.teachmeskills.springbootproject.constants.RequestAttributesNames;
import by.teachmeskills.springbootproject.constants.SessionAttributesNames;
import by.teachmeskills.springbootproject.constants.Values;
import by.teachmeskills.springbootproject.entities.PagingParams;
import by.teachmeskills.springbootproject.services.ProductService;
import com.opencsv.exceptions.CsvDataTypeMismatchException;
import com.opencsv.exceptions.CsvRequiredFieldEmptyException;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.IOException;
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

    @PostMapping("/csv/exportProducts")
    public void exportProductsToCsv(@RequestParam(RequestAttributesNames.CATEGORY_NAME) String categoryName,
                                   HttpServletResponse response) throws IOException, CsvRequiredFieldEmptyException, CsvDataTypeMismatchException {
        productService.saveToFile(categoryName, response);
    }

    @PostMapping ("/csv/importProducts")
    public ModelAndView importProductsFromCsv(@RequestParam(RequestAttributesNames.CATEGORY_NAME) String categoryName,
                                             @RequestParam(RequestAttributesNames.FILE) MultipartFile file) throws IOException {
        return productService.loadFromFile(categoryName, file);
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
