package by.teachmeskills.springbootproject.controllers;

import by.teachmeskills.springbootproject.constants.PagesPaths;
import by.teachmeskills.springbootproject.constants.RequestAttributesNames;
import by.teachmeskills.springbootproject.constants.SessionAttributesNames;
import by.teachmeskills.springbootproject.entities.Cart;
import by.teachmeskills.springbootproject.exceptions.InsufficientFundsException;
import by.teachmeskills.springbootproject.exceptions.NoProductsInOrderException;
import by.teachmeskills.springbootproject.exceptions.NoResourceFoundException;
import by.teachmeskills.springbootproject.utils.SecurityContextUtils;
import by.teachmeskills.springbootproject.services.ProductService;
import by.teachmeskills.springbootproject.services.UserService;
import lombok.RequiredArgsConstructor;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("/cart")
@SessionAttributes(SessionAttributesNames.CART)
@RequiredArgsConstructor
public class CartController {

    private final ProductService productService;
    private final UserService userService;

    @GetMapping
    public ModelAndView openCartPage(@ModelAttribute(SessionAttributesNames.CART) Cart cart) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.CART_PAGE);
        modelAndView.addObject(RequestAttributesNames.CART, cart);
        return new ModelAndView(PagesPaths.CART_PAGE);
    }

    @GetMapping("/addProduct/{id}")
    public ModelAndView addProduct(@PathVariable int id, @ModelAttribute(SessionAttributesNames.CART) Cart cart) throws NoResourceFoundException {
        return productService.addProductToCart(id, cart);
    }

    @GetMapping("/removeProduct/{id}")
    public ModelAndView removeProduct(@PathVariable int id, @ModelAttribute(SessionAttributesNames.CART) Cart cart) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.CART_PAGE);
        cart.removeProduct(id);
        modelAndView.addObject(RequestAttributesNames.CART, cart);
        return modelAndView;
    }

    @GetMapping("/clear")
    public ModelAndView clearCart(@ModelAttribute(SessionAttributesNames.CART) Cart cart) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.CART_PAGE);
        cart.clear();
        modelAndView.addObject(RequestAttributesNames.CART, cart);
        return modelAndView;
    }


    @GetMapping("/makeOrder")
    @PreAuthorize("isAuthenticated()")
    public ModelAndView makeOrder(@ModelAttribute(SessionAttributesNames.CART) Cart cart)
            throws InsufficientFundsException, NoProductsInOrderException, NoResourceFoundException {
        return userService.makeOrder(SecurityContextUtils.getUser().orElse(null), cart);
    }


    @ModelAttribute(SessionAttributesNames.CART)
    public Cart initializeCartInSession() {
        return new Cart();
    }
}
