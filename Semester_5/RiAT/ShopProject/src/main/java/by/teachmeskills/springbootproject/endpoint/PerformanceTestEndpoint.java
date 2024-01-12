package by.teachmeskills.springbootproject.endpoint;

import by.teachmeskills.springbootproject.entities.Product;
import by.teachmeskills.springbootproject.entities.SearchCriteria;
import by.teachmeskills.springbootproject.repositories.CategoryRepository;
import by.teachmeskills.springbootproject.repositories.ProductRepository;
import by.teachmeskills.springbootproject.repositories.ProductSearchSpecification;
import by.teachmeskills.springbootproject.repositories.UserRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.boot.actuate.endpoint.annotation.Endpoint;
import org.springframework.boot.actuate.endpoint.annotation.ReadOperation;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Component;
import org.springframework.ui.ModelMap;
import org.springframework.util.StopWatch;
import org.springframework.web.servlet.ModelAndView;

@Component
@Endpoint(id = "performanceTest")
@RequiredArgsConstructor
public class PerformanceTestEndpoint {

    private final UserRepository userRepository;
    private final CategoryRepository categoryRepository;
    private final ProductRepository productRepository;

    @ReadOperation
    public ModelAndView getResults() {
        ModelAndView modelAndView = new ModelAndView("performanceInfo");
        ModelMap modelMap = new ModelMap();
        long lastResult;
        StopWatch watch = new StopWatch();

        watch.start();
        categoryRepository.findAll();
        watch.stop();
        lastResult = watch.getTotalTimeNanos();
        modelMap.addAttribute("categoriesReadResult", lastResult);

        watch = new StopWatch();
        watch.start();
        productRepository.findAll();
        watch.stop();
        lastResult = watch.getTotalTimeNanos();
        modelMap.addAttribute("productsReadResult", lastResult);

        watch = new StopWatch();
        watch.start();
        productRepository.findById(2);
        watch.stop();
        lastResult = watch.getTotalTimeNanos();
        modelMap.addAttribute("productFindResult", lastResult);

        watch = new StopWatch();
        watch.start();
        SearchCriteria searchCriteriaDto = new SearchCriteria();
        searchCriteriaDto.setKeyWords("Последнее желание");
        Specification<Product> specification = new ProductSearchSpecification(searchCriteriaDto);
        productRepository.findAll(specification);
        watch.stop();
        lastResult = watch.getTotalTimeNanos();
        modelMap.addAttribute("productsFindResult", lastResult);

        watch = new StopWatch();
        watch.start();
        userRepository.findById(3);
        watch.stop();
        lastResult = watch.getTotalTimeNanos();
        modelMap.addAttribute("userFindResult", lastResult);

        modelAndView.addAllObjects(modelMap);
        return modelAndView;
    }
}
