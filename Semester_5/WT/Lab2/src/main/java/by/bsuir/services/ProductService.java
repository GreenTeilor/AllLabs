package by.bsuir.services;

import by.bsuir.constants.ExceptionMessages;
import by.bsuir.constants.PagesPaths;
import by.bsuir.constants.RequestAttributesNames;
import by.bsuir.domain.Product;
import by.bsuir.exceptions.ConnectionException;
import by.bsuir.exceptions.DbException;
import by.bsuir.exceptions.ServiceException;
import by.bsuir.repositories.ProductRepository;
import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.NoArgsConstructor;

import java.io.IOException;
import java.sql.SQLException;
import java.util.Optional;

@NoArgsConstructor
public class ProductService {
    private final ProductRepository productRepository = new ProductRepository();

    /**
     * Returns the product page by product id.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @param id product id
     * @throws ServiceException if occurs dispatch error
     * @throws DbException  if occurs db error
     */
    public void getProduct(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet,
                                    String id) throws DbException, ServiceException {
        try {
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.PRODUCT_PAGE + PagesPaths.POSTFIX);
            if (!id.matches("\\d+")) {
                throw new NumberFormatException("id is not a number");
            }
            Optional<Product> product = productRepository.getProductById(Integer.parseInt(id));
            request.setAttribute(RequestAttributesNames.PRODUCT, product.orElseThrow(() ->
                    new IOException("No product with given id")));
            product.ifPresent(p -> request.setAttribute(RequestAttributesNames.PRODUCT, p));
            requestDispatcher.forward(request, response);
        } catch (ConnectionException | SQLException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        } catch (ServletException | IOException | NumberFormatException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }
}
