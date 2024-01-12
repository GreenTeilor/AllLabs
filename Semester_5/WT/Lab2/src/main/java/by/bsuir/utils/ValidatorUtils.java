package by.bsuir.utils;

import by.bsuir.constants.Messages;
import by.bsuir.constants.RequestAttributesNames;
import by.bsuir.constants.RequestParams;
import jakarta.servlet.http.HttpServletRequest;

import java.util.regex.Pattern;

public class ValidatorUtils {
    private final static String ERROR = "Error";

    private ValidatorUtils() {

    }

    public static boolean validateRegistration(HttpServletRequest request) {
        String name = request.getParameter(RequestParams.NAME);
        String lastName = request.getParameter(RequestParams.LAST_NAME);
        String email = request.getParameter(RequestParams.EMAIL);
        String birthDate = request.getParameter(RequestParams.BIRTH_DATE);
        String password = request.getParameter(RequestParams.PASSWORD);
        boolean status = true;
        Pattern emailPattern = Pattern.compile("^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,6}$", Pattern.CASE_INSENSITIVE);
        if (!name.matches("[A-Za-z]+")) {
            request.setAttribute(RequestAttributesNames.NAME + ERROR, Messages.NAME_ERROR);
            status = false;
        }
        if (!lastName.matches("[A-Za-z]+")) {
            request.setAttribute(RequestAttributesNames.LAST_NAME + ERROR, Messages.LAST_NAME_ERROR);
            status = false;
        }
        if (!emailPattern.matcher(email).matches()) {
            request.setAttribute(RequestAttributesNames.EMAIL + ERROR, Messages.EMAIL_ERROR);
            status = false;
        }
        if (!DateValidatorUsingDateFormatUtils.isValid("yyyy-MM-dd", birthDate)) {
            request.setAttribute(RequestAttributesNames.BIRTH_DATE + ERROR, Messages.DATE_ERROR);
            status = false;
        }
        if (!(password.length() > 2)) {
            request.setAttribute(RequestAttributesNames.PASSWORD + ERROR, Messages.PASSWORD_ERROR);
            status = false;
        }
        return status;
    }

    public static boolean validateAddressAndPhoneNumber(HttpServletRequest request) {
        String address = request.getParameter(RequestParams.ADDRESS);
        String phoneNumber = request.getParameter(RequestParams.PHONE_NUMBER);
        boolean status = true;
        if (address.length() < 10 || address.length() > 90) {
            request.setAttribute(RequestAttributesNames.ADDRESS + ERROR, Messages.ADDRESS_ERROR);
            status = false;
        }
        if (!phoneNumber.matches("^\\+375((29)|(44)|(25)|(33))[0-9]{7}$")) {
            request.setAttribute(RequestAttributesNames.PHONE_NUMBER + ERROR, Messages.PHONE_NUMBER_ERROR);
            status = false;
        }
        return status;
    }
}
