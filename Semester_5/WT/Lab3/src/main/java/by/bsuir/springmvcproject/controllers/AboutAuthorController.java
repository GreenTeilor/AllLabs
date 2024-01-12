package by.bsuir.springmvcproject.controllers;

import by.bsuir.springmvcproject.constants.PagesPaths;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("/about")
public class AboutAuthorController {
    @GetMapping
    public ModelAndView openAboutAuthorPage() {
        return new ModelAndView(PagesPaths.ABOUT_PAGE);
    }
}
