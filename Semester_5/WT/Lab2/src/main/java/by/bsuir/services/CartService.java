package by.bsuir.services;

import by.bsuir.constants.ExceptionMessages;
import by.bsuir.constants.Messages;
import by.bsuir.constants.PagesPaths;
import by.bsuir.constants.RequestAttributesNames;
import by.bsuir.constants.SessionAttributesNames;
import by.bsuir.constants.Values;
import by.bsuir.domain.Cart;
import by.bsuir.domain.User;
import by.bsuir.exceptions.ConnectionException;
import by.bsuir.exceptions.DbException;
import by.bsuir.exceptions.ServiceException;
import by.bsuir.repositories.ProductRepository;
import by.bsuir.repositories.UserRepository;
import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import lombok.NoArgsConstructor;

import java.io.IOException;
import java.math.BigDecimal;
import java.sql.SQLException;

@NoArgsConstructor
public class CartService {
    private final ProductRepository productRepository = new ProductRepository();
    private final UserRepository userRepository = new UserRepository();

    /**
     * Returns the card page.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @throws ServiceException if occurs dispatch error
     */
    public void getCart(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet)
            throws ServiceException {
        try {
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.CART_PAGE + PagesPaths.POSTFIX);
            requestDispatcher.forward(request, response);
        } catch (ServletException | IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }

    /**
     * Allows to add product to cart.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param id an {@link HttpServletResponse} product id
     * @throws ServiceException if occurs dispatch error
     * @throws DbException      if occurs db error
     */
    public void addProduct(HttpServletRequest request, HttpServletResponse response, String id)
            throws ServiceException, DbException {
        try {
            if (!id.matches("\\d+")) {
                throw new NumberFormatException("id is not a number");
            }
            ((Cart) request.getSession().getAttribute(SessionAttributesNames.CART)).addProduct(productRepository.
                    getProductById(Integer.parseInt(id)).orElseThrow(() -> new IOException("No product with given id")));
            response.sendRedirect(request.getContextPath() + "/products/" + id);
        } catch (IOException | NumberFormatException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        } catch (SQLException | ConnectionException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        }
    }

    /**
     * Allows to remove product from cart.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @param id an {@link HttpServletResponse} product id
     * @throws ServiceException if occurs dispatch error
     */
    public void removeProduct(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet, String id)
            throws ServiceException {
        try {
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.CART_PAGE + PagesPaths.POSTFIX);
            if (!id.matches("\\d+")) {
                throw new NumberFormatException("id is not a number");
            }
            ((Cart) request.getSession().getAttribute(SessionAttributesNames.CART)).removeProduct(Integer.parseInt(id));
            requestDispatcher.forward(request, response);
        } catch (IOException | NumberFormatException | ServletException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }

    /**
     * Allows to clear cart.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @throws ServiceException if occurs dispatch error
     */
    public void clearCart(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet)
            throws ServiceException {
        try {
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.CART_PAGE + PagesPaths.POSTFIX);
            ((Cart) request.getSession().getAttribute(SessionAttributesNames.CART)).clear();
            requestDispatcher.forward(request, response);
        } catch (IOException | NumberFormatException | ServletException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }

    /**
     * Allows to clear cart.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @throws ServiceException if occurs dispatch error
     * @throws DbException      if occurs db error
     */
    public void makeOrder(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet) throws DbException, ServiceException {
        try {
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.CART_PAGE + PagesPaths.POSTFIX);
            HttpSession session = request.getSession();
            User user = (User) session.getAttribute(SessionAttributesNames.USER);
            Cart cart = (Cart) session.getAttribute(SessionAttributesNames.CART);
            if (userRepository.getUserBalance(user.getId()).subtract(cart.getPrice()).compareTo(BigDecimal.ZERO) >= 0) {
                if (!cart.isEmpty()) {
                    user.getOrders().add(userRepository.makeOrder(cart, user.getId()));
                    user.setBalance(user.getBalance().subtract(cart.getPrice()));
                    request.setAttribute(RequestAttributesNames.COLOR, Values.SUCCESS_COLOR);
                    request.setAttribute(RequestAttributesNames.STATUS, Messages.COMPLETED);
                    cart.clear();
                } else {
                    request.setAttribute(RequestAttributesNames.COLOR, Values.ERROR_COLOR);
                    request.setAttribute(RequestAttributesNames.STATUS, Messages.EMPTY_CART);
                }
            } else {
                request.setAttribute(RequestAttributesNames.COLOR, Values.ERROR_COLOR);
                request.setAttribute(RequestAttributesNames.STATUS, Messages.INSUFFICIENT_FUNDS);
            }
            requestDispatcher.forward(request, response);
        } catch (ConnectionException | SQLException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        } catch (ServletException | IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }
}
