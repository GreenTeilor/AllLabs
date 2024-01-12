<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>

<html>
<head>
    <title>Home</title>
    <jsp:include page="dependencies.jsp"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="<c:url value="/style/pagination.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/common.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/home.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/footer.css"/>" rel="stylesheet">
</head>
<body class="d-flex flex-column min-vh-100">
<div class="wrapper">
    <jsp:include page="header.jsp"/>
    <div class="main">
        <c:if test="${user != null}">
            <jsp:include page="info.jsp"/>
        </c:if>
        <div class="container-fluid categories">
            <div class="row">
                <c:forEach items="${categories}" var="item">
                    <div class="col d-flex justify-content-center">
                        <div class="card"
                             style="width: 22rem; margin: 20px 0 20px 0; background-color: #dee2e6 !important; border-radius: 40px;">
                            <a href="<c:url value="/categories/${item.getName()}"/>"><img
                                    src="<c:url value="/${item.getImagePath()}"/>"
                                    class="card-img-top"
                                    style="height: 25rem; border-radius: 40px 40px 0 0;"
                                    alt="..."></a>
                            <div class="card-body" style="text-align: center">
                                <h2 class="card-title">${item.getName()}</h2>
                                <a href="<c:url value="/categories/${item.getName()}"/>"
                                   class="btn btn-primary">Перейти</a>
                            </div>
                        </div>
                    </div>
                </c:forEach>
            </div>
        </div>
        <c:set var="params" value="${categoryPagingParams}"/>
        <div class="pagination-management">
            <nav class="pagination-nav">
                <ul class="pagination">
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/home/paging?pageNumber=${params.getPageNumber() - 1}"/>"><<</a>
                    </li>
                    <li class="page-item"><a class="page-link" href="<c:url value="/home/paging?pageNumber=1"/>">1</a>
                    </li>
                    <li class="page-item"><a class="page-link" href="<c:url value="/home/paging?pageNumber=2"/>">2</a>
                    </li>
                    <li class="page-item"><a class="page-link" href="<c:url value="/home/paging?pageNumber=3"/>">3</a>
                    </li>
                    <li class="page-item"><a class="page-link"
                                             href="<c:url value="/home/paging?pageNumber=${params.getPageNumber() + 1}"/>">>></a>
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
                           href="<c:url value="/home/paging?pageSize=${pageSize}"/>">${pageSize}</a>
                    </c:forEach>
                </div>
            </div>
        </div>
    </div>
    <jsp:include page="footer.jsp"/>
</div>
</body>
</html>
