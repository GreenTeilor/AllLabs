<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jstl/core" %>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>
<%@ page import="by.bsuir.springmvcproject.constants.SessionAttributesNames" %>
<%@ page import="by.bsuir.springmvcproject.entities.Cart" %>
<%@ page import="by.bsuir.springmvcproject.constants.SessionAttributesNames" %>

<header>
    <nav class="navbar navbar-expand-lg navbar-light bg-light">

        <div class="container-fluid">
            <a class="navbar-brand" href="<c:url value="/home"/>">
                <img src="<c:url value="/assets/books.png"/>" width="30" height="30"
                     class="d-inline-block align-top" alt="">
                Книжечки
            </a>
            <button class="navbar-toggler" type="button" data-toggle="collapse"
                    data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false"
                    aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarSupportedContent">
                <ul class="navbar-nav">
                    <li class="nav-item">
                        <a class="nav-link" href="<c:url value="/home"/>">&#127968 Главная</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" href="<c:url value="/about"/>">&#10067 Об авторе</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" href="<c:url value="/profile"/>">&#128188 Профиль</a>
                    </li>
                    <%
                        Cart cart = (Cart) request.getSession().getAttribute(SessionAttributesNames.CART);
                        String productsInCart = (cart != null && cart.size() != 0) ? String.valueOf(cart.size()) : "";
                    %>
                    <li class="nav-item">
                        <a class="nav-link" href="<c:url value="/cart"/>">&#128722 Корзина<sup
                                style="color: red; font-weight: bold; font-size: 1rem;"><%=productsInCart%>
                        </sup></a>
                    </li>
                    <li>
                        <a class="nav-link" href="<c:url value="/search"/>">&#128269 Поиск</a>
                    </li>
                    <sec:authorize access="hasRole('ADMIN')">
                        <li>
                            <a class="nav-link" href="<c:url value="/admin"/>">&#128297 Администрирование</a>
                        </li>
                    </sec:authorize>
                </ul>
            </div>

            <sec:authorize access="!isAuthenticated()">
                <div class="d-flex align-items-center">
                    <a href="<c:url value="/login"/>" type="button" class="btn btn-primary px-3 me-2">
                        Логин
                    </a>
                    <a href="<c:url value="/register"/>" type="button" class="btn btn-primary me-3">
                        Регистрация
                    </a>
                </div>
            </sec:authorize>
            <sec:authorize access="isAuthenticated()">
                <div class="d-flex align-items-center">
                    <a href="<c:url value="/logout"/>" type="button" class="btn btn-primary me-3">
                        Выйти
                    </a>
                </div>
            </sec:authorize>

        </div>
    </nav>
</header>