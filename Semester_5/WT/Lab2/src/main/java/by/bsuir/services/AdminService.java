package by.bsuir.services;

import by.bsuir.constants.ExceptionMessages;
import by.bsuir.constants.PagesPaths;
import by.bsuir.constants.RequestAttributesNames;
import by.bsuir.constants.RequestParams;
import by.bsuir.domain.Category;
import by.bsuir.domain.PagingParams;
import by.bsuir.domain.Product;
import by.bsuir.exceptions.ConnectionException;
import by.bsuir.exceptions.DbException;
import by.bsuir.exceptions.ServiceException;
import by.bsuir.repositories.CategoryRepository;
import by.bsuir.repositories.ProductRepository;
import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;
import lombok.NoArgsConstructor;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigDecimal;
import java.nio.file.StandardCopyOption;
import java.sql.SQLException;

@NoArgsConstructor
public class AdminService {
    private final CategoryRepository categoryRepository = new CategoryRepository();
    private final ProductRepository productRepository = new ProductRepository();

    /**
     * Returns the admin page.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} Provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @throws ServiceException if occurs dispatch error
     * @throws DbException      if occurs db error
     */
    public void getAdminPage(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet)
            throws ServiceException, DbException {

        RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                PagesPaths.ADMIN_PAGE + PagesPaths.POSTFIX);
        try {
            request.setAttribute(RequestAttributesNames.CATEGORIES, categoryRepository.getCategories(
                    new PagingParams(0, 1000_000)));
            requestDispatcher.forward(request, response);
        } catch (ServletException | IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        } catch (SQLException | ConnectionException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        }
    }

    /**
     * Allows to add new category.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @throws ServiceException if occurs dispatch error
     * @throws DbException      if occurs db error
     */
    public void addCategory(HttpServletRequest request, HttpServletResponse response) throws ServiceException, DbException {
        try {
            String name = request.getParameter(RequestParams.CATEGORY_NAME);
            Part filePart = request.getPart(RequestParams.CATEGORY_FILE);
            String fileName = filePart.getSubmittedFileName();
            fileName = name + "." + fileName.split("\\.")[1];
            InputStream fileContent = filePart.getInputStream();
            java.nio.file.Files.copy(
                    fileContent,
                    new File("D:\\Labs\\semester_5\\WT\\Lab2\\src\\main\\webapp\\assets\\" + fileName).toPath(),
                    StandardCopyOption.REPLACE_EXISTING);
            categoryRepository.persist(Category.
                    builder().
                    name(name).
                    imagePath("assets/" + fileName).
                    build());
            response.sendRedirect(request.getContextPath() + "/admin");
        } catch (IOException | ServletException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        } catch (SQLException | ConnectionException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        }
    }

    /**
     * Allows to add new product.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @throws ServiceException if occurs dispatch error
     * @throws DbException      if occurs db error
     */
    public void addProduct(HttpServletRequest request, HttpServletResponse response) throws ServiceException, DbException {
        try {
            String name = request.getParameter(RequestParams.PRODUCT_NAME);
            String description = request.getParameter(RequestParams.PRODUCT_DESCRIPTION);
            Part filePart = request.getPart(RequestParams.PRODUCT_FILE);
            String category = request.getParameter(RequestParams.PRODUCT_CATEGORY);
            BigDecimal price = new BigDecimal(request.getParameter(RequestParams.PRODUCT_PRICE));
            String fileName = filePart.getSubmittedFileName();
            fileName = name + "." + fileName.split("\\.")[1];
            InputStream fileContent = filePart.getInputStream();
            java.nio.file.Files.copy(
                    fileContent,
                    new File("D:\\Labs\\semester_5\\WT\\Lab2\\src\\main\\webapp\\assets\\" + fileName).toPath(),
                    StandardCopyOption.REPLACE_EXISTING);
            productRepository.persist(Product.
                    builder().
                    name(name).
                    description(description).
                    imagePath("assets/" + fileName).
                    category(category).
                    price(price).
                    build());
            response.sendRedirect(request.getContextPath() + "/admin");
        } catch (IOException | ServletException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        } catch (SQLException | ConnectionException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        }
    }
}
