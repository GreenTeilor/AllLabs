package by.teachmeskills.springbootproject.utils;

import org.springframework.validation.BindingResult;
import org.springframework.web.servlet.ModelAndView;

import java.util.Objects;

public class ErrorPopulatorUtils {

    public static void populateError(String field, ModelAndView modelAndView, BindingResult bindingResult) {
        if (bindingResult.hasFieldErrors(field)) {
            modelAndView.addObject(field + "Error", Objects.requireNonNull(bindingResult.getFieldError(field))
                    .getDefaultMessage());
        }
    }
}