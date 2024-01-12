package by.bsuir.listeners;

import by.bsuir.constants.SessionAttributesNames;
import by.bsuir.constants.Values;
import by.bsuir.domain.Cart;
import by.bsuir.domain.PagingParams;
import jakarta.servlet.annotation.WebListener;
import jakarta.servlet.http.HttpSession;
import jakarta.servlet.http.HttpSessionEvent;
import jakarta.servlet.http.HttpSessionListener;

@WebListener
public class SessionListener implements HttpSessionListener {
    @Override
    public void sessionCreated(HttpSessionEvent session) {
        HttpSession httpSession = session.getSession();
        httpSession.setAttribute(SessionAttributesNames.USER, null);
        httpSession.setAttribute(SessionAttributesNames.CATEGORY_PAGING_PARAMS,
                new PagingParams(Values.DEFAULT_START_PAGE, Values.DEFAULT_PAGE_SIZE));
        httpSession.setAttribute(SessionAttributesNames.PRODUCT_PAGING_PARAMS,
                new PagingParams(Values.DEFAULT_START_PAGE, Values.DEFAULT_PAGE_SIZE));
        httpSession.setAttribute(SessionAttributesNames.ORDER_PAGING_PARAMS,
                new PagingParams(Values.DEFAULT_START_PAGE, Values.DEFAULT_PAGE_SIZE));
        httpSession.setAttribute(SessionAttributesNames.CART, new Cart());
    }
}
