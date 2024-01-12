package by.bsuir.springmvcproject.controllers;

import by.bsuir.springmvcproject.constants.SessionAttributesNames;
import by.bsuir.springmvcproject.services.UserService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("/login")
@SessionAttributes(SessionAttributesNames.USER)
@RequiredArgsConstructor
public class LoginController {
    private final UserService userService;

    @GetMapping
    public ModelAndView openLoginPage(@RequestParam(name = "error", required = false) String error) {
        return userService.processLoginPage(error);
    }
}
