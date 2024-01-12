<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<html>
<head>
    <title>${requestScope.product.getName()}</title>
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
        <div class="container">
            <div class="card">
                <div class="card-body">
                    <h3 class="card-title">${requestScope.product.getName()}</h3>
                    <h6 class="card-subtitle">Жанр: ${requestScope.product.getCategory()}</h6>
                    <div class="row">
                        <div class="col-lg-5">
                            <div class="white-box text-left">
                                <img alt="product-image" src="<c:url value="/${requestScope.product.getImagePath()}"/>" class="img-responsive bookImg">
                            </div>
                        </div>
                        <div class="col-lg-7 justify-content: right">
                            <h4 class="box-title mt-5">Описание</h4>
                            <p>${requestScope.product.getDescription()}</p>
                            <h2 class="mt-5">
                                <fmt:formatNumber value="${requestScope.product.getPrice()}"
                                                  type="currency"/>
                            </h2>
                            <a href="<c:url value="/cart/addProduct/${requestScope.product.getId()}"/>"
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
