package by.bsuir.springmvcproject.exceptions;

import by.bsuir.springmvcproject.constants.PagesPaths;
import by.bsuir.springmvcproject.constants.RequestAttributesNames;
import jakarta.servlet.ServletContext;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.AccessDeniedException;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.servlet.ModelAndView;

import java.io.IOException;

@ControllerAdvice
@RequiredArgsConstructor
@Slf4j
public class GlobalControllerExceptionHandler {

    private final ServletContext context;

    @ExceptionHandler(NoResourceFoundException.class)
    public ResponseEntity<String> handleNoResourceFoundException(NoResourceFoundException e) {
        return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);
    }

    @ExceptionHandler(AccessDeniedException.class)
    @ResponseStatus(HttpStatus.OK)
    public void handleForbiddenException(Exception e, HttpServletResponse response) throws IOException {
        response.sendRedirect(context.getContextPath() + "/login");
    }

    @ExceptionHandler(Exception.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public ModelAndView handleException(Exception e) {
        log.error(e.getMessage());
        ModelAndView modelAndView = new ModelAndView(PagesPaths.ERROR_PAGE);
        modelAndView.addObject("info", e.getMessage());
        return modelAndView;
    }

    @ExceptionHandler(UserAlreadyExistsException.class)
    @ResponseStatus(HttpStatus.OK)
    public ModelAndView handleUserAlreadyExistsException(UserAlreadyExistsException e) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.REGISTER_PAGE);
        modelAndView.addObject(RequestAttributesNames.STATUS, e.getMessage());
        modelAndView.addObject(RequestAttributesNames.COLOR, "red");
        return modelAndView;
    }

    @ExceptionHandler(AuthorizationException.class)
    @ResponseStatus(HttpStatus.OK)
    public ModelAndView handleAuthorizationException(AuthorizationException e) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.LOGIN_PAGE);
        modelAndView.addObject(RequestAttributesNames.STATUS, e.getMessage());
        return modelAndView;
    }

    @ExceptionHandler({InsufficientFundsException.class, NoProductsInOrderException.class})
    @ResponseStatus(HttpStatus.OK)
    public ModelAndView handleOrderMakingExceptions(Exception e) {
        ModelAndView modelAndView = new ModelAndView(PagesPaths.CART_PAGE);
        modelAndView.addObject(RequestAttributesNames.STATUS, e.getMessage());
        modelAndView.addObject(RequestAttributesNames.COLOR, "red");
        return modelAndView;
    }
}

