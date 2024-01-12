<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib uri='http://java.sun.com/jsp/jstl/core' prefix='c' %>

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
                        <a class="nav-link" href="<c:url value="/profile"/>">&#128188 Профиль</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" href="<c:url value="/cart"/>">&#128722 Корзина
                            <c:if test="${sessionScope.cart.size() != 0}">
                                <sup style="color: red; font-weight: bold; font-size: 1rem;">
                                        ${sessionScope.cart.size()}
                                </sup>
                            </c:if>
                        </a>
                    </li>
                    <c:if test="${sessionScope.user != null && sessionScope.user.hasRole(\"ROLE_ADMIN\")}">
                        <li>
                            <a class="nav-link" href="<c:url value="/admin"/>">&#128297 Администрирование</a>
                        </li>
                    </c:if>
                    <li>
                        <div class="language">
                            <img src="<c:url value="/assets/lang_ru.png"/>" alt="ru" data-google-lang="ru"
                                 class="language_img">
                            <img src="<c:url value="/assets/lang_en.png"/>" alt="en" data-google-lang="en"
                                 class="language_img">
                        </div>
                    </li>
                </ul>
            </div>

            <c:choose>
                <c:when test="${sessionScope.user == null}">
                    <div class="d-flex align-items-center">
                        <a href="<c:url value="/login"/>" type="button" class="btn btn-primary px-3 me-2">
                            Логин
                        </a>
                        <a href="<c:url value="/registration"/>" type="button" class="btn btn-primary me-3">
                            Регистрация
                        </a>
                    </div>
                </c:when>
                <c:otherwise>
                    <div class="d-flex align-items-center">
                        <a href="<c:url value="/home/logout"/>" type="button" class="btn btn-primary me-3">
                            Выйти
                        </a>
                    </div>
                </c:otherwise>
            </c:choose>
        </div>
    </nav>
</header>