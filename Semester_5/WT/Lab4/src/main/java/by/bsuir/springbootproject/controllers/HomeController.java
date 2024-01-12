package by.bsuir.springbootproject.controllers;

import by.bsuir.springbootproject.constants.RequestAttributesNames;
import by.bsuir.springbootproject.constants.SessionAttributesNames;
import by.bsuir.springbootproject.constants.Values;
import by.bsuir.springbootproject.entities.PagingParams;
import by.bsuir.springbootproject.utils.SecurityContextUtils;
import by.bsuir.springbootproject.services.CategoryService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.servlet.ModelAndView;

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

