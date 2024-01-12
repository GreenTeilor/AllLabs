<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<html>
<head>
    <title>Поиск</title>
    <jsp:include page="dependencies.jsp"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="<c:url value="/style/pagination.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/admin.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/common.css"/>" rel="stylesheet">
    <link href="<c:url value="/style/footer.css"/>" rel="stylesheet">
</head>
<body>
<div class="wrapper">
    <jsp:include page="header.jsp"/>
    <div class="main">
        <div class="container-fluid">
            <div class="row filter-and-content">
                <div class="col-md-6 d-flex justify-content-center align-items-center">
                    <div class="filter">
                        <div class="items-group main-text">
                            Новая категория
                        </div>
                        <form method="POST" action="<c:url value="/admin/addCategory"/>" enctype="multipart/form-data">
                            <div class="items-group">
                                <div>
                                    <label for="categoryName">Название</label>
                                </div>
                                <input id="categoryName" name="categoryName" type="text" placeholder="Название">
                            </div>
                            <div class="items-group">
                                <div>
                                    <label for="categoryFile">Изображение</label>
                                </div>
                                <div class="files">
                                        <label class="label">
                                            <i>&#128204</i>
                                            <input id="categoryFile" name="categoryFile" type="file" class="title" accept=".png,.jpg,.jpeg">
                                        </label>
                                </div>
                                <div>
                                    <button class="btn btn-primary">Добавить</button>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>
                <div class="col-md-6 d-flex justify-content-center align-items-center">
                    <div class="filter">
                        <div class="items-group main-text">
                            Новый продукт
                        </div>
                        <form method="POST" action="<c:url value="/admin/addProduct"/>" enctype="multipart/form-data">
                            <div class="items-group">
                                <div>
                                    <label for="productName">Название</label>
                                </div>
                                <input id="productName" name="productName" type="text" placeholder="Название">
                            </div>
                            <div class="items-group">
                                <div>
                                    <label for="productDescription">Описание</label>
                                </div>
                                <textarea id="productDescription" maxlength="350" cols="30" name="productDescription" placeholder="Описание">

                                </textarea>
                            </div>
                            <div class="items-group">
                                <div>
                                    <label for="productCategory">Категория</label>
                                </div>
                                <select id="productCategory" name="productCategory">
                                    <c:forEach items="${requestScope.categories}" var="category">
                                        <option name="category"
                                                value="${category.getName()}">${category.getName()}</option>
                                    </c:forEach>
                                </select>
                            </div>
                            <div class="items-group">
                                <div>
                                    <label for="productPrice">Цена</label>
                                </div>
                                <input id="productPrice" name="productPrice" type="text" placeholder="Цена">
                            </div>
                            <div class="items-group">
                                <div>
                                    <label for="productFile">Изображение</label>
                                </div>
                                <div class="files">
                                    <label class="label">
                                        <i>&#128204</i>
                                        <input id="productFile" name="productFile" type="file" class="title" accept=".png,.jpg,.jpeg">
                                    </label>
                                </div>
                                <div>
                                    <button class="btn btn-primary">Добавить</button>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <jsp:include page="footer.jsp"/>
</div>
</body>
</html>
