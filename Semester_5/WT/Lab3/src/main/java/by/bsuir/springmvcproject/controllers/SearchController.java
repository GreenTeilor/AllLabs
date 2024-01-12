package by.bsuir.springmvcproject.controllers;

import by.bsuir.springmvcproject.constants.SessionAttributesNames;
import by.bsuir.springmvcproject.constants.Values;
import by.bsuir.springmvcproject.entities.SearchCriteria;
import by.bsuir.springmvcproject.services.ProductService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("/search")
@SessionAttributes(SessionAttributesNames.SEARCH_CRITERIA)
@RequiredArgsConstructor
public class SearchController {
    private final ProductService productService;

    @GetMapping
    public ModelAndView openSearchPage(@ModelAttribute(SessionAttributesNames.SEARCH_CRITERIA) SearchCriteria searchCriteria) {
        return productService.findProducts(searchCriteria);
    }

    @PostMapping
    public ModelAndView search(@RequestParam String keyWords, @ModelAttribute(SessionAttributesNames.SEARCH_CRITERIA) SearchCriteria searchCriteria) {
        searchCriteria.setKeyWords(keyWords);
        searchCriteria.setPageNumber(Values.DEFAULT_START_PAGE);
        return productService.findProducts(searchCriteria);
    }

    @GetMapping("/paging")
    public ModelAndView changePagingParams(@ModelAttribute(SessionAttributesNames.SEARCH_CRITERIA) SearchCriteria searchCriteria) {
        return productService.findProducts(searchCriteria);
    }

    @PostMapping("setFilter")
    public ModelAndView setFilter(@ModelAttribute(SessionAttributesNames.SEARCH_CRITERIA) SearchCriteria searchCriteria) {
        return productService.changeFilter(searchCriteria, searchCriteria.getSearchCategory(), searchCriteria.getPriceFrom(), searchCriteria.getPriceTo());
    }

    @GetMapping("resetFilter")
    public ModelAndView resetFilter(@ModelAttribute(SessionAttributesNames.SEARCH_CRITERIA) SearchCriteria searchCriteria) {
        return productService.changeFilter(searchCriteria, null, null, null);
    }

    @ModelAttribute(SessionAttributesNames.SEARCH_CRITERIA)
    public SearchCriteria initializeSearchCriteria() {
        return SearchCriteria.builder().
                pageNumber(Values.DEFAULT_START_PAGE).
                pageSize(Values.DEFAULT_PAGE_SIZE).
                keyWords("").
                build();
    }
}
