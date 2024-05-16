package by.bsuir.springbootproject.controllers;

import by.bsuir.springbootproject.constants.PagesPaths;
import by.bsuir.springbootproject.constants.RequestAttributesNames;
import by.bsuir.springbootproject.entities.User;
import by.bsuir.springbootproject.exceptions.UserAlreadyExistsException;
import by.bsuir.springbootproject.services.UserService;
import by.bsuir.springbootproject.utils.ErrorPopulatorUtils;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("/register")
@RequiredArgsConstructor
public class RegisterController {

    private final UserService service;

    @GetMapping
    public ModelAndView openRegisterPage() {
        return new ModelAndView(PagesPaths.REGISTER_PAGE);
    }

    @PostMapping
    public ModelAndView registerUser(@Valid @ModelAttribute(RequestAttributesNames.USER) User user, BindingResult bindingResult) throws UserAlreadyExistsException {
        if (bindingResult.hasErrors()) {
            ModelAndView modelAndView = new ModelAndView(PagesPaths.REGISTER_PAGE);
            ErrorPopulatorUtils.populateError(RequestAttributesNames.NAME, modelAndView, bindingResult);
            ErrorPopulatorUtils.populateError(RequestAttributesNames.LAST_NAME, modelAndView, bindingResult);
            ErrorPopulatorUtils.populateError(RequestAttributesNames.EMAIL, modelAndView, bindingResult);
            ErrorPopulatorUtils.populateError(RequestAttributesNames.PASSWORD, modelAndView, bindingResult);
            ErrorPopulatorUtils.populateError(RequestAttributesNames.BIRTH_DATE, modelAndView, bindingResult);
            return modelAndView;
        } else {
            return service.create(user);
        }
    }
}
