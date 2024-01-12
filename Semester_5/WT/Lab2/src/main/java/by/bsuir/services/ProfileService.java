package by.bsuir.services;

import by.bsuir.constants.ExceptionMessages;
import by.bsuir.constants.PagesPaths;
import by.bsuir.constants.RequestAttributesNames;
import by.bsuir.constants.RequestParams;
import by.bsuir.constants.SessionAttributesNames;
import by.bsuir.domain.PagingParams;
import by.bsuir.domain.Statistics;
import by.bsuir.domain.User;
import by.bsuir.exceptions.ConnectionException;
import by.bsuir.exceptions.DbException;
import by.bsuir.exceptions.ServiceException;
import by.bsuir.repositories.UserRepository;
import by.bsuir.utils.ValidatorUtils;
import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import lombok.NoArgsConstructor;

import java.io.IOException;
import java.sql.SQLException;

@NoArgsConstructor
public class ProfileService {
    private final UserRepository userRepository = new UserRepository();

    /**
     * Returns the user profile page.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @throws ServiceException if occurs dispatch error
     * @throws DbException  if occurs db error
     */
    public void getUserInfo(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet) throws DbException, ServiceException {
        try {
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.PROFILE_PAGE + PagesPaths.POSTFIX);
            HttpSession session = request.getSession();
            int userId = ((User) session.getAttribute(SessionAttributesNames.USER)).getId();
            Statistics statistics = userRepository.getStatistics(userId);
            request.setAttribute(RequestAttributesNames.STATISTICS, statistics);
            request.setAttribute(RequestAttributesNames.ORDERS, userRepository.getOrders(userId,
                    (PagingParams) session.getAttribute(SessionAttributesNames.ORDER_PAGING_PARAMS)));
            requestDispatcher.forward(request, response);
        } catch (SQLException | ConnectionException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        } catch (ServletException | IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }

    /**
     * Allows paging orders on profile page.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @throws ServiceException if occurs dispatch error
     * @throws DbException  if occurs db error
     */
    public void paging(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet)
            throws DbException, ServiceException {
        try {
            HttpSession session = request.getSession();
            User user = (User) session.getAttribute(SessionAttributesNames.USER);
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.PROFILE_PAGE + PagesPaths.POSTFIX);
            request.setAttribute(RequestAttributesNames.ORDERS, userRepository.getOrders(user.getId(),
                    PagingUtils.updatePagingParams(request, SessionAttributesNames.ORDER_PAGING_PARAMS)));
            request.setAttribute(RequestAttributesNames.STATISTICS, userRepository.getStatistics(user.getId()));
            requestDispatcher.forward(request, response);
        } catch (SQLException | ConnectionException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        } catch (ServletException | IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }

    /**
     * Allows to add address and phoneNumber for user.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @throws ServiceException if occurs dispatch error
     * @throws DbException  if occurs db error
     */
    public void addAddressAndPhoneNumber(HttpServletRequest request, HttpServletResponse response)
            throws DbException, ServiceException {
        try {
            if (ValidatorUtils.validateAddressAndPhoneNumber(request)) {
                HttpSession session = request.getSession();
                User user = (User) session.getAttribute(SessionAttributesNames.USER);
                String address = request.getParameter(RequestParams.ADDRESS);
                String phoneNumber = request.getParameter(RequestParams.PHONE_NUMBER);
                userRepository.updateAddressAndPhoneNumber(address, phoneNumber, user.getId());
                user.setAddress(address);
                user.setPhoneNumber(phoneNumber);
            }
            response.sendRedirect(request.getContextPath() + "/profile");
        } catch (IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        } catch (SQLException | ConnectionException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        }
    }
}
