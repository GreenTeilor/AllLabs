package by.teachmeskills.springbootproject.controllers;

import by.teachmeskills.springbootproject.constants.RequestAttributesNames;
import by.teachmeskills.springbootproject.constants.SessionAttributesNames;
import by.teachmeskills.springbootproject.constants.Values;
import by.teachmeskills.springbootproject.entities.BaseEntity;
import by.teachmeskills.springbootproject.entities.PagingParams;
import by.teachmeskills.springbootproject.entities.User;
import by.teachmeskills.springbootproject.utils.SecurityContextUtils;
import by.teachmeskills.springbootproject.services.UserService;
import com.opencsv.exceptions.CsvDataTypeMismatchException;
import com.opencsv.exceptions.CsvRequiredFieldEmptyException;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.IOException;

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

    @PostMapping("/csv/exportOrders")
    public void exportOrdersToCsv(HttpServletResponse response) throws CsvRequiredFieldEmptyException, CsvDataTypeMismatchException, IOException {
        userService.saveOrdersToFile(SecurityContextUtils.getUser().map(BaseEntity::getId).orElse(null), response);
    }

    @PostMapping("/csv/importOrders")
    public ModelAndView importOrdersFromCsv(@RequestParam(RequestAttributesNames.FILE) MultipartFile file) throws IOException {
        return userService.loadOrdersFromFile(SecurityContextUtils.getUser().orElse(null), file);
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
