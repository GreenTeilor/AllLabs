<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<html>
<head>
    <title>${productName}</title>
    <jsp:include page="dependencies.jsp"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
    <link href="<c:url value="/style/product.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/common.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/footer.css"/>" rel="stylesheet">
</head>
<body>
<div class="wrapper">
    <jsp:include page="header.jsp"/>
    <div class="main">
        <c:set var="product" value="${product}"/>
        <div class="container">
            <div class="card">
                <div class="card-body">
                    <h3 class="card-title">${product.getName()}</h3>
                    <div class="h-flex">
                        <h6 class="card-subtitle p-2">Жанр: ${product.getCategory().getName()}</h6>
                        <h6 class="card-subtitle p-2">Автор: ${product.getAuthor().getName()}</h6>
                        <h6 class="card-subtitle p-2">Издатель: ${product.getPublisher().getName()}</h6>
                    </div>
                    <div class="row">
                        <div class="col-lg-5">
                            <div class="white-box text-left">
                                <div id="carousel${product.getId()}" class="carousel slide" data-ride="carousel">
                                    <div class="carousel-inner">
                                        <c:forEach items="${product.getImages()}" var="image" varStatus="status">
                                            <div class="carousel-item ${status.first ? 'active' : ''}">
                                                <img src="<c:url value="/${image.getPath()}"/>"
                                                     class="img-responsive bookImg">
                                            </div>
                                        </c:forEach>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <div class="col-lg-7 justify-content: right">
                            <h4 class="box-title mt-5">Описание</h4>
                            <p>${product.getDescription()}</p>

                            <div>
                                <c:forEach items="${product.getLabels()}" var="label">
                                    <div class="label-box">
                                            ${label.getName()}
                                    </div>
                                </c:forEach>
                            </div>

                            <h2 class="mt-5">
                                <fmt:formatNumber value="${product.getPrice()}"
                                                  type="currency"/>
                            </h2>

                            <a href="<c:url value="/cart/addProduct/${product.getId()}"/>"
                               class="btn btn-primary btn-rounded">Купить</a>

                            <h3 class="box-title mt-5">Почему мы?</h3>
                            <ul class="list-unstyled">
                                <li><i class="fa fa-check text-success"></i>Работаем 20 лет</li>
                                <li><i class="fa fa-check text-success"></i>Быстрая доставка по всей Беларуси</li>
                                <li><i class="fa fa-check text-success"></i>Большой выбор</li>
                                <li><i class="fa fa-check text-success"></i>Скидки постоянным клиентам</li>
                            </ul>
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
