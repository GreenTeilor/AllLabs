package by.bsuir.springmvcproject.controllers;

import by.bsuir.springmvcproject.exceptions.NoResourceFoundException;
import by.bsuir.springmvcproject.services.ProductService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("/products")
@RequiredArgsConstructor
public class ProductController {
    private final ProductService service;

    @GetMapping("/{id}")
    public ModelAndView openProductPage(@PathVariable int id) throws NoResourceFoundException {
        return service.getProductById(id);
    }

}
