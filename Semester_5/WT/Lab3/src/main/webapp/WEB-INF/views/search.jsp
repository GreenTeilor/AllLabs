<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<html>
<head>
    <title>Поиск</title>
    <jsp:include page="dependencies.jsp"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="<c:url value="/style/pagination.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/search.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/common.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/footer.css"/>" rel="stylesheet">
</head>
<body>
<div class="wrapper">
    <jsp:include page="header.jsp"/>
    <div class="main">
        <c:set var="user" value="${sessionScope.searchCriteria}"/>
        <form class="well form-inline search-form" method="POST" action="<c:url value="/search"/>">
            <input type="text" name="keyWords" id="keyWords" class="span3" placeholder="Поиск">
            <button type="submit" class="btn btn-primary">Найти</button>
        </form>
        <div class="container-fluid">
            <div class="row filter-and-content">
                <div class="col-md-5 d-flex justify-content-center align-items-center">
                    <div class="filter">
                        <div class="items-group main-text">
                            Фильтр
                        </div>
                        <form method="POST" action="<c:url value="/search/setFilter"/>">
                            <div class="items-group">
                                <div>
                                    <label for="searchCategory">Категория</label>
                                </div>
                                <select id="searchCategory" name="searchCategory">
                                    <c:forEach items="${categories}" var="category">
                                        <option name="category"
                                                <c:if test="${searchCriteria.getSearchCategory().equals(category.getName())}">selected</c:if>
                                                value="${category.getName()}">${category.getName()}</option>
                                    </c:forEach>
                                </select>
                            </div>
                            <div class="items-group">
                                <div>
                                    Цена
                                </div>
                                <input id="priceFrom" name="priceFrom" type="text" placeholder="От"
                                       <c:if test="${searchCriteria.getPriceFrom() != null}">value="${searchCriteria.getPriceFrom()}"</c:if>>
                                <input id="priceTo" name="priceTo" type="text" placeholder="До"
                                       <c:if test="${searchCriteria.getPriceTo() != null}">value="${searchCriteria.getPriceTo()}"</c:if>>
                                <div>
                                    <button class="btn btn-primary">Применить</button>
                                </div>
                            </div>
                        </form>
                        <c:if test="${searchCriteria.getSearchCategory() != null || searchCriteria.getPriceFrom() != null || searchCriteria.getPriceTo() != null}">
                            <div class="filter_reset">
                                <a class="btn btn-primary" href="<c:url value="/search/resetFilter"/>">Сбросить</a>
                                <span style="color: green;">Активирован</span>
                            </div>
                        </c:if>
                    </div>
                </div>
                <div class="col-md-7 d-flex justify-content-center align-items-center">
                    <div class="content">
                        <div class="items-group main-text">
                            Найденные товары
                        </div>
                        <div class="products">
                            <c:forEach items="${products}" var="product">
                                <div style="display: inline-block;">
                                    <div class="card" style="width: 15rem; margin: 10px; background-color: #dee2e6">
                                        <a href="<c:url value="/products/${product.getId()}"/>"><img
                                                src="<c:url value="/${product.getImagePath()}"/>"
                                                class="card-img-top"
                                                style="height: 17rem;"
                                                alt="..."></a>
                                        <div class="card-body" style="text-align: center">
                                            <h2 class="card-title" style="font-size: 1rem;">${product.getName()}</h2>
                                            <p class="card-text">Цена: <fmt:formatNumber value="${product.getPrice()}"
                                                                                         type="currency"/><br></p>
                                            <a href="<c:url value="/products/${product.getId()}"/>"
                                               class="btn btn-primary">Посмотреть</a>
                                        </div>
                                    </div>
                                </div>
                            </c:forEach>
                        </div>
                        <c:set var="params" value="${searchCriteria}"/>
                        <div class="pagination-management">
                            <nav class="pagination-nav">
                                <ul class="pagination">
                                    <li class="page-item"><a class="page-link"
                                                             href="<c:url value="/search/paging?pageNumber=${params.getPageNumber() - 1}"/>"><<</a>
                                    </li>
                                    <li class="page-item"><a class="page-link"
                                                             href="<c:url value="/search/paging?pageNumber=1"/>">1</a>
                                    </li>
                                    <li class="page-item"><a class="page-link"
                                                             href="<c:url value="/search/paging?pageNumber=2"/>">2</a>
                                    </li>
                                    <li class="page-item"><a class="page-link"
                                                             href="<c:url value="/search/paging?pageNumber=3"/>">3</a>
                                    </li>
                                    <li class="page-item"><a class="page-link"
                                                             href="<c:url value="/search/paging?pageNumber=${params.getPageNumber() + 1}"/>">>></a>
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
                                           href="<c:url value="/search/paging?pageSize=${pageSize}"/>">${pageSize}</a>
                                    </c:forEach>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <jsp:include page="footer.jsp"/>
</div>
</body>
</html>
