<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>

<html>
<head>
    <title>Профиль</title>
    <jsp:include page="dependencies.jsp"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="<c:url value="/style/pagination.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/common.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/profile.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/footer.css"/>" rel="stylesheet">
</head>
<body>
<div class="wrapper">
    <jsp:include page="header.jsp"/>
    <div class="main">
        <c:set var="user" value="${user}"/>
        <c:set var="statistics" value="${statistics}"/>
        <section class="section about-section gray-bg" id="about">
            <div class="container">
                <div class="row align-items-center flex-row-reverse">
                    <div class="col-lg-6 justify-content-center d-flex">
                        <div class="about-text go-to">
                            <h3 class="dark-color">Профиль</h3>
                            <div class="row about-list">
                                <div class="col-md-6">
                                    <div class="media">
                                        <label>Имя</label>
                                        <p>${user.getName()}</p>
                                    </div>
                                    <div class="media">
                                        <label>Фамилия</label>
                                        <p>${user.getLastName()}</p>
                                    </div>
                                    <div class="media">
                                        <label>email</label>
                                        <p>${user.getEmail()}</p>
                                    </div>
                                </div>
                                <div class="col-md-6">
                                    <div class="media">
                                        <label>Дата рождения</label>
                                        <p>${user.getBirthDate()}</p>
                                    </div>
                                    <c:choose>
                                        <c:when test="${user.getAddress() != null && user.getPhoneNumber() != null}">
                                            <div class="media">
                                                <label>Адрес</label>
                                                <p>${user.getAddress()}</p>
                                            </div>
                                            <div class="media">
                                                <label>Телефон</label>
                                                <p>${user.getPhoneNumber()}</p>
                                            </div>
                                        </c:when>
                                        <c:otherwise>
                                            <form method="POST" action="<c:url value="/profile"/>">
                                                <div class="media">
                                                    <label for="address">Адрес</label>
                                                    <div>
                                                        <input class="info-input" type="text" name="address"
                                                               id="address"
                                                               placeholder="Адрес">
                                                    </div>
                                                    <div class="errorInput">${addressError}</div>
                                                </div>
                                                <div class="media">
                                                    <label for="phoneNumber">Номер телефона</label>
                                                    <div>
                                                        <input class="info-input" type="tel" name="phoneNumber"
                                                               id="phoneNumber"
                                                               placeholder="Номер телефона">
                                                    </div>
                                                    <div class="errorInput">${phoneNumberError}</div>
                                                </div>
                                                <button class="input-button btn btn-primary" type="submit">Отправить
                                                </button>
                                            </form>
                                        </c:otherwise>
                                    </c:choose>

                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="col-lg-6 justify-content-center d-flex">
                        <div class="about-avatar">
                            <img src="<c:url value="/assets/avatar.png"/>" title="avatar" alt="avatar">
                        </div>
                    </div>
                </div>
                <div class="counter">
                    <div class="row">
                        <div class="col-md-6 col-lg-3">
                            <div class="count-data text-center">
                                <h6 class="count h2" data-to="500" data-speed="500">${statistics.getDaysRegistered()}
                                    дней</h6>
                                <p class="m-0px font-w-600">С нами</p>
                            </div>
                        </div>
                        <div class="col-md-6 col-lg-3">
                            <div class="count-data text-center">
                                <h6 class="count h2" data-to="150" data-speed="150">${statistics.getOrderCount()}</h6>
                                <p class="m-0px font-w-600">Сделано заказов</p>
                            </div>
                        </div>
                        <div class="col-md-6 col-lg-3">
                            <div class="count-data text-center">
                                <h6 class="count h2" data-to="850" data-speed="850">${statistics.getBooksCount()}</h6>
                                <p class="m-0px font-w-600">Куплено книг</p>
                            </div>
                        </div>
                        <div class="col-md-6 col-lg-3">
                            <div class="count-data text-center">
                                <h6 class="count h2" data-to="190"
                                    data-speed="190">${statistics.getFavoriteCategory()}</h6>
                                <p class="m-0px font-w-600">Любимый жанр</p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </section>
        <section>
            <div class="history">
                <div class="count-data text-center">
                    <h6 class="count h2" data-to="500" data-speed="500">История заказов</h6>
                </div>
            </div>

            <c:forEach items="${orders}" var="order">
                <div class="history">
                    <div class="generalData">
                        <div style="display: inline-block;">
                            <span>Заказ: ${order.getId()} </span>
                        </div>
                        <div style="display: inline-block;">
                            <span>Дата: ${order.getDate()}</span>
                        </div>
                        <div style="display: inline-block;">
                <span>Цена: <fmt:formatNumber value="${order.getPrice()}"
                                              type="currency"/></span>
                        </div>
                    </div>
                    <div style="text-align: center">
                        <c:forEach items="${order.getProducts()}" var="product">
                            <div style="display: inline-block;">
                                <div class="card" style="width: 15rem; margin: 20px; background-color: #dee2e6">
                                    <a href="<c:url value="/products/${product.getId()}"/>"><img
                                            src="<c:url value="/${product.getImagePath()}"/>"
                                            class="card-img-top"
                                            style="height: 17rem;"
                                            alt="..."></a>
                                    <div class="card-body" style="text-align: center">
                                        <h2 class="card-title" style="font-size: 1rem;">${product.getName()}</h2>
                                        <p class="card-text">Цена: <fmt:formatNumber value="${product.getPrice()}"
                                                                                     type="currency"/><br></p>
                                        <a href="<c:url value="/products/${product.getId()}"/>" class="btn btn-primary">Посмотреть</a>
                                    </div>
                                </div>
                            </div>
                        </c:forEach>
                    </div>
                </div>
            </c:forEach>

        </section>
        <c:set var="params" value="${orderPagingParams}"/>
        <div class="pagination-management">
            <nav class="pagination-nav">
                <ul class="pagination">
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/profile/paging?pageNumber=${params.getPageNumber() - 1}"/>"><<</a>
                    </li>
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/profile/paging?pageNumber=1"/>">1</a></li>
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/profile/paging?pageNumber=2"/>">2</a></li>
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/profile/paging?pageNumber=3"/>">3</a></li>
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/profile/paging?pageNumber=${params.getPageNumber() + 1}"/>">>></a>
                    </li>
                </ul>
            </nav>
            <div class="dropdown">
                <button class="btn btn-secondary dropdown-toggle" type="button" id="dropdownMenuButton"
                        data-toggle="dropdown"
                        aria-haspopup="true" aria-expanded="false">
                    Размер
                </button>
                <div class="dropdown-menu" aria-labelledby="dropdownMenuButton">
                    <c:forEach begin="1" end="9" var="pageSize">
                        <a class="dropdown-item"
                           href="<c:url value="/profile/paging?pageSize=${pageSize}"/>">${pageSize}</a>
                    </c:forEach>
                </div>
            </div>
        </div>
    </div>
    <jsp:include page="footer.jsp"/>
</div>
</body>
</html>