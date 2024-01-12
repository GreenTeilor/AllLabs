package by.bsuir.services;

import by.bsuir.constants.ExceptionMessages;
import by.bsuir.constants.PagesPaths;
import by.bsuir.constants.RequestAttributesNames;
import by.bsuir.constants.SessionAttributesNames;
import by.bsuir.domain.PagingParams;
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

@NoArgsConstructor
public class CategoryService {
    private final ProductRepository productRepository = new ProductRepository();

    /**
     * Returns the category page.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @param category an {@link HttpServletResponse} category name
     * @throws ServiceException if occurs dispatch error
     * @throws DbException  if occurs db error
     */
    public void getCategoryProducts(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet,
                                    String category) throws DbException, ServiceException {
        try {
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.CATEGORY_PAGE + PagesPaths.POSTFIX);
            PagingParams productPaging = (PagingParams) request.getSession().getAttribute(SessionAttributesNames.
                    PRODUCT_PAGING_PARAMS);
            request.setAttribute(RequestAttributesNames.CATEGORY_PRODUCTS, productRepository.getProductsByCategory(
                    category, productPaging));
            request.setAttribute(RequestAttributesNames.CATEGORY_NAME, category);
            requestDispatcher.forward(request, response);
        } catch (ConnectionException | SQLException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        } catch (ServletException | IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }

    /**
     * Allows paging on category page.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @param category an {@link HttpServletResponse} category name
     * @throws ServiceException if occurs dispatch error
     * @throws DbException  if occurs db error
     */
    public void paging(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet, String category)
            throws DbException, ServiceException {
        try {
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.CATEGORY_PAGE + PagesPaths.POSTFIX);
            request.setAttribute(RequestAttributesNames.CATEGORY_PRODUCTS, productRepository.
                    getProductsByCategory(category, PagingUtils.updatePagingParams(request,
                            SessionAttributesNames.PRODUCT_PAGING_PARAMS)));
            request.setAttribute(RequestAttributesNames.CATEGORY_NAME, category);
            requestDispatcher.forward(request, response);
        } catch (ConnectionException | SQLException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        } catch (ServletException | IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }
}
