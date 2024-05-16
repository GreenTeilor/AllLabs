package by.bsuir.springbootproject.controllers;

import by.bsuir.springbootproject.constants.SessionAttributesNames;
import by.bsuir.springbootproject.constants.Values;
import by.bsuir.springbootproject.entities.PagingParams;
import by.bsuir.springbootproject.entities.User;
import by.bsuir.springbootproject.utils.SecurityContextUtils;
import by.bsuir.springbootproject.services.UserService;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("/profile")
@SessionAttributes(SessionAttributesNames.ORDER_PAGING_PARAMS)
@RequiredArgsConstructor
public class ProfileController {

    private final UserService userService;

    @GetMapping
    public ModelAndView openProfilePage(@ModelAttribute(SessionAttributesNames.ORDER_PAGING_PARAMS) PagingParams params) {
        return userService.getUserInfo(SecurityContextUtils.getUser().orElse(null), params);
    }

    @PostMapping
    public ModelAndView addAddressAndPhoneNumberInfo(@Valid @ModelAttribute(SessionAttributesNames.USER) User user, BindingResult bindingResult,
                                                     @ModelAttribute(SessionAttributesNames.ORDER_PAGING_PARAMS) PagingParams params) {
        return userService.addAddressAndPhoneNumberInfo(user.getAddress(), user.getPhoneNumber(), SecurityContextUtils.getUser().orElse(null), bindingResult, params);
    }

    @GetMapping("/paging")
    public ModelAndView changePagingParams(@ModelAttribute(SessionAttributesNames.ORDER_PAGING_PARAMS) PagingParams params) {
        return userService.getUserInfo(SecurityContextUtils.getUser().orElse(null), params);
    }

    @ModelAttribute(SessionAttributesNames.ORDER_PAGING_PARAMS)
    public PagingParams initializePagingParams() {
        return new PagingParams(Values.DEFAULT_START_PAGE, Values.DEFAULT_PAGE_SIZE);
    }

}
