package by.bsuir.springbootproject.controllers;

import by.bsuir.springbootproject.constraints.NumberConstraint;
import by.bsuir.springbootproject.dto.OrderDto;
import by.bsuir.springbootproject.dto.CartDto;
import by.bsuir.springbootproject.dto.complex.MakeOrderRequestDto;
import by.bsuir.springbootproject.exceptions.InsufficientFundsException;
import by.bsuir.springbootproject.exceptions.NoProductsInOrderException;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.services.ProductService;
import by.bsuir.springbootproject.services.UserService;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.Parameter;
import io.swagger.v3.oas.annotations.media.Content;
import io.swagger.v3.oas.annotations.media.Schema;
import io.swagger.v3.oas.annotations.responses.ApiResponse;
import io.swagger.v3.oas.annotations.responses.ApiResponses;
import io.swagger.v3.oas.annotations.tags.Tag;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.validation.BindingResult;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@Tag(name = "cart", description = "Cart endpoints")
@RestController
@RequestMapping("/cart")
@RequiredArgsConstructor
@Validated
public class CartController {

    private final ProductService productService;
    private final UserService userService;

    @Operation(
            summary = "Add product",
            description = "Add product to cart")
    @ApiResponses(value = {
            @ApiResponse(
                    responseCode = "200",
                    description = "Product was added to cart",
                    content = @Content(schema = @Schema(implementation = CartDto.class))
            ),
            @ApiResponse(
                    responseCode = "404",
                    description = "Product not found",
                    content = @Content(schema = @Schema(implementation = String.class))
            )
    })
    @PostMapping("/addProduct/{id}")
    public CartDto addProduct(@Parameter(description = "Product id") @NumberConstraint @PathVariable String id,
                              @io.swagger.v3.oas.annotations.parameters.RequestBody(description = "Cart object") @Valid @RequestBody CartDto cartDto,
                              BindingResult bindingResult) throws NoResourceFoundException {
        return productService.addProductToCart(Integer.parseInt(id), cartDto);
    }

    @Operation(
            summary = "Remove product",
            description = "Remove product from cart")
    @ApiResponses(value = {
            @ApiResponse(
                    responseCode = "200",
                    description = "Product was removed from cart",
                    content = @Content(schema = @Schema(implementation = CartDto.class))
            )
    })
    @DeleteMapping("/removeProduct/{id}")
    public CartDto removeProduct(@Parameter(description = "Product id") @NumberConstraint @PathVariable String id,
                                 @io.swagger.v3.oas.annotations.parameters.RequestBody(description = "Cart object") @Valid @RequestBody CartDto cartDto,
                                 BindingResult bindingResult) {
        return productService.removeProductFromCart(Integer.parseInt(id), cartDto);
    }

    @Operation(
            summary = "Clear cart",
            description = "Remove all products from cart")
    @ApiResponses(value = {
            @ApiResponse(
                    responseCode = "200",
                    description = "Products were removed from cart",
                    content = @Content(schema = @Schema(implementation = CartDto.class))
            )
    })
    @DeleteMapping("/clear")
    public CartDto clear(@io.swagger.v3.oas.annotations.parameters.RequestBody(description = "Cart object") @Valid @RequestBody CartDto cartDto,
                         BindingResult bindingResult) {
        return productService.removeAllProductsFromCart(cartDto);
    }

    @Operation(
            summary = "Make order",
            description = "Make order based on what cart contains and user id")
    @ApiResponses(value = {
            @ApiResponse(
                    responseCode = "200",
                    description = "Order was made\tInsufficient funds\tNo products in cart",
                    content = {@Content(schema = @Schema(implementation = OrderDto.class)),
                            @Content(schema = @Schema(implementation = String.class))}
            ),
    })
    @PostMapping("/makeOrder")
    public OrderDto makeOrder(@io.swagger.v3.oas.annotations.parameters.RequestBody(description = "Request object with cart and userId") @Valid @RequestBody MakeOrderRequestDto orderRequestDto,
                              BindingResult bindingResult) throws InsufficientFundsException, NoProductsInOrderException, NoResourceFoundException {
        return userService.makeOrder(userService.getUserById(orderRequestDto.getUserId()), orderRequestDto.getCartDto());
    }
}
