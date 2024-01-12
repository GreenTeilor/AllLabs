package by.bsuir.springmvcproject.controllers;

import by.bsuir.springmvcproject.constants.PagesPaths;
import by.bsuir.springmvcproject.constants.RequestAttributesNames;
import by.bsuir.springmvcproject.constants.SessionAttributesNames;
import by.bsuir.springmvcproject.entities.Cart;
import by.bsuir.springmvcproject.exceptions.InsufficientFundsException;
import by.bsuir.springmvcproject.exceptions.NoProductsInOrderException;
import by.bsuir.springmvcproject.exceptions.NoResourceFoundException;
import by.bsuir.springmvcproject.utils.SecurityContextUtils;
import by.bsuir.springmvcproject.services.ProductService;
import by.bsuir.springmvcproject.services.UserService;
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
