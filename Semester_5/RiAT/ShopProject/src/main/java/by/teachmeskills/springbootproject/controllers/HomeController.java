package by.teachmeskills.springbootproject.controllers;

import by.teachmeskills.springbootproject.constants.RequestAttributesNames;
import by.teachmeskills.springbootproject.constants.SessionAttributesNames;
import by.teachmeskills.springbootproject.constants.Values;
import by.teachmeskills.springbootproject.entities.PagingParams;
import by.teachmeskills.springbootproject.utils.SecurityContextUtils;
import by.teachmeskills.springbootproject.services.CategoryService;
import com.opencsv.exceptions.CsvDataTypeMismatchException;
import com.opencsv.exceptions.CsvRequiredFieldEmptyException;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.IOException;

@Controller
@RequestMapping("/home")
@SessionAttributes(SessionAttributesNames.CATEGORY_PAGING_PARAMS)
@RequiredArgsConstructor
public class HomeController {
    private final CategoryService categoryService;

    @GetMapping
    public ModelAndView openHomePage(@ModelAttribute(SessionAttributesNames.CATEGORY_PAGING_PARAMS) PagingParams params) {
        ModelAndView modelAndView = categoryService.read(params);
        modelAndView.addObject(RequestAttributesNames.USER, SecurityContextUtils.getUser().orElse(null));
        return modelAndView;
    }

    @PostMapping("/csv/exportCategories")
    public void exportCategoriesToCsv(HttpServletResponse response) throws IOException, CsvRequiredFieldEmptyException, CsvDataTypeMismatchException {
        categoryService.saveToFile(response);
    }

    @PostMapping("/csv/importCategories")
    public ModelAndView importCategoriesFromCsv(@RequestParam(RequestAttributesNames.FILE) MultipartFile file) throws IOException {
        return categoryService.loadFromFile(file);
    }

    @GetMapping("/paging")
    public ModelAndView changePagingParams(@ModelAttribute(SessionAttributesNames.CATEGORY_PAGING_PARAMS) PagingParams params) {
        ModelAndView modelAndView = categoryService.read(params);
        modelAndView.addObject(RequestAttributesNames.USER, SecurityContextUtils.getUser().orElse(null));
        return modelAndView;
    }

    @ModelAttribute(SessionAttributesNames.CATEGORY_PAGING_PARAMS)
    public PagingParams initializePagingParams() {
        return new PagingParams(Values.DEFAULT_START_PAGE, Values.DEFAULT_PAGE_SIZE);
    }
}

