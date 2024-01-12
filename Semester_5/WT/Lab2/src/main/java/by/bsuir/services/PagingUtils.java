package by.bsuir.services;

import by.bsuir.constants.RequestAttributesNames;
import by.bsuir.domain.PagingParams;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpSession;

public class PagingUtils {
    private PagingUtils() {

    }

    /**
     * Returns the home page.
     * <p>
     *
     * @param request  an {@link HttpServletRequest} object that contains the request the client has made of the servlet
     * @param sessionAttributeName name of attribute, responsible for pagination on certain page
     */
    public static PagingParams updatePagingParams(HttpServletRequest request, String sessionAttributeName) {
        HttpSession session = request.getSession();
        PagingParams params = (PagingParams) session.getAttribute(sessionAttributeName);
        String pageNumber = request.getParameter(RequestAttributesNames.PAGE_NUMBER);
        String pageSize = request.getParameter(RequestAttributesNames.PAGE_SIZE);
        int iPageNumber;
        int iPageSize;
        if (pageNumber != null) {
            if (pageNumber.matches("\\d+")) {
                iPageNumber = Integer.parseInt(pageNumber);
                params.setPageNumber(iPageNumber);
            }
        }
        if (pageSize != null) {
            if (pageSize.matches("\\d+")) {
                iPageSize = Integer.parseInt(pageSize);
                params.setPageSize(iPageSize);
            }
        }
        session.setAttribute(sessionAttributeName, params);
        return params;
    }
}
