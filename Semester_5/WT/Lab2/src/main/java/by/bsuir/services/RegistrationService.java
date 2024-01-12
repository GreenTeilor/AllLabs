package by.bsuir.services;

import by.bsuir.constants.ExceptionMessages;
import by.bsuir.constants.Messages;
import by.bsuir.constants.PagesPaths;
import by.bsuir.constants.RequestAttributesNames;
import by.bsuir.constants.RequestParams;
import by.bsuir.constants.Values;
import by.bsuir.domain.User;
import by.bsuir.exceptions.ConnectionException;
import by.bsuir.exceptions.DbException;
import by.bsuir.exceptions.ServiceException;
import by.bsuir.repositories.UserRepository;
import by.bsuir.utils.HashUtils;
import by.bsuir.utils.ValidatorUtils;
import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.NoArgsConstructor;

import java.io.IOException;
import java.math.BigDecimal;
import java.sql.SQLException;
import java.time.LocalDate;

@NoArgsConstructor
public class RegistrationService {
    private final UserRepository userRepository = new UserRepository();

    /**
     * Returns the registration page.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @throws ServiceException if occurs dispatch error
     */
    public void getRegistrationPage(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet) throws ServiceException {
        try {
            RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                    PagesPaths.REGISTRATION_PAGE + PagesPaths.POSTFIX);
            requestDispatcher.forward(request, response);
        } catch (ServletException | IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        }
    }

    /**
     * Allows to register user.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param response an {@link HttpServletResponse} object that contains the response the servlet sends to the client
     * @param servlet  an {@link HttpServlet} provides an abstract class to be subclassed to create an HTTP servlet suitable for a Web site
     * @throws ServiceException if occurs dispatch error
     * @throws DbException  if occurs db error
     */
    public void registerUser(HttpServletRequest request, HttpServletResponse response, HttpServlet servlet) throws ServiceException, DbException {
        RequestDispatcher requestDispatcher = servlet.getServletContext().getRequestDispatcher(PagesPaths.PREFIX +
                PagesPaths.REGISTRATION_PAGE + PagesPaths.POSTFIX);
        try {
            if (ValidatorUtils.validateRegistration(request)) {
                User user = User.
                        builder().
                        id(0).
                        name(request.getParameter(RequestParams.NAME)).
                        lastName(request.getParameter(RequestParams.LAST_NAME)).
                        email(request.getParameter(RequestParams.EMAIL)).
                        birthDate(LocalDate.parse(request.getParameter(RequestParams.BIRTH_DATE))).
                        registrationDate(LocalDate.now()).
                        balance(BigDecimal.ZERO).
                        password(HashUtils.getHash(request.getParameter(RequestParams.PASSWORD))).
                        address(null).
                        phoneNumber(null).
                        build();
                if (userRepository.isPresent(user.getEmail())) {
                    request.setAttribute(RequestAttributesNames.COLOR, Values.ERROR_COLOR);
                    request.setAttribute(RequestAttributesNames.STATUS, Messages.USER_EXISTS_ERROR);
                } else {
                    userRepository.persist(user);
                    request.setAttribute(RequestAttributesNames.COLOR, Values.SUCCESS_COLOR);
                    request.setAttribute(RequestAttributesNames.STATUS, Messages.SUCCESS);
                }
            }
            requestDispatcher.forward(request, response);
        } catch (ServletException | IOException e) {
            throw new ServiceException(ExceptionMessages.SERVICE_EXCEPTION);
        } catch (SQLException | ConnectionException e) {
            throw new DbException(ExceptionMessages.DB_EXCEPTION);
        }
    }
}
