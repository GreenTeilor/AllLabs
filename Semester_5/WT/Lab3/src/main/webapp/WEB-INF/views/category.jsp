<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>

<html>
<head>
    <title>${categoryName}</title>
    <jsp:include page="dependencies.jsp"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="<c:url value="/style/pagination.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/common.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/category.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/footer.css"/>" rel="stylesheet">
</head>
<body>
<div class="wrapper">
    <jsp:include page="header.jsp"/>
    <div class="main">
        <div class="container-fluid products">
            <div class="row">
                <c:forEach items="${categoryProducts}" var="product">
                    <div class="col d-flex justify-content-center">
                        <div class="card" style="width: 22rem; margin: 20px 0 20px 0; background-color: #dee2e6">
                            <a href="<c:url value="/products/${product.getId()}"/>"><img
                                    src="<c:url value="/${product.getImagePath()}"/>" class="card-img-top"
                                    style="height: 25rem;" alt="..."></a>
                            <div class="card-body" style="text-align: center">
                                <h2 class="card-title">${product.getName()}</h2>
                                <p class="card-text"><span
                                        style="color: green; font-size: 1.5rem;">Цена: <fmt:formatNumber
                                        value="${product.getPrice()}"
                                        type="currency"/></span><br>
                                        ${product.getDescription()}</p>
                                <a href="<c:url value="/products/${product.getId()}"/>"
                                   class="btn btn-primary">Посмотреть</a>
                            </div>
                        </div>
                    </div>
                </c:forEach>
            </div>
        </div>
        <c:set var="params" value="${productPagingParams}"/>
        <div class="pagination-management">
            <nav class="pagination-nav">
                <ul class="pagination">
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/categories/${categoryName}/paging?pageNumber=${params.getPageNumber() - 1}"/>"><<</a>
                    </li>
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/categories/${categoryName}/paging?pageNumber=1"/>">1</a>
                    </li>
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/categories/${categoryName}/paging?pageNumber=2"/>">2</a>
                    </li>
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/categories/${categoryName}/paging?pageNumber=3"/>">3</a>
                    </li>
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/categories/${categoryName}/paging?pageNumber=${params.getPageNumber() + 1}"/>">>></a>
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
                           href="<c:url value="/categories/${categoryName}/paging?pageSize=${pageSize}"/>">${pageSize}</a>
                    </c:forEach>
                </div>
            </div>
        </div>
    </div>
    <jsp:include page="footer.jsp"/>
</div>
</body>
</html>
