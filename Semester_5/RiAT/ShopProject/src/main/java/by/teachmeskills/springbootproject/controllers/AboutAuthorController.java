package by.teachmeskills.springbootproject.controllers;

import by.teachmeskills.springbootproject.constants.PagesPaths;
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
