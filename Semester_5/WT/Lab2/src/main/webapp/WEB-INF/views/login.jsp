<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jstl/core" %>

<html>
<head>
    <title>Login</title>
    <jsp:include page="dependencies.jsp"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="<c:url value="/style/login_register.css"/>" rel="stylesheet">
</head>
<body>
<div class="wrapper">
    <div class="logo">
        <img src="<c:url value="/assets/books.png"/>" alt="">
    </div>
    <div class="text-center mt-4 name">
        Вход
    </div>
    <form class="p-3 mt-3" method="POST" action="<c:url value="/login"/>">
        <div class="form-field d-flex align-items-center">
            <label for="email"></label><input type="email" name="email" id="email" placeholder="Email">
        </div>
        <div class="errorInput">${requestScope.emailError}</div>
        <div class="form-field d-flex align-items-center">
            <label for="password"></label><input type="password" name="password" id="password" placeholder="Пароль">
        </div>
        <div class="errorInput">${requestScope.passwordError}</div>
        <button type="submit" class="btn mt-3">Логин</button>
    </form>
    <div class="text-center fs-6">
        <span style="color: black">Нет аккаунта?</span> <a href="<c:url value="/registration"/>">Зарегистрироваться</a>
    </div>
    <div class="text-center fs-6">
        <span class="status">${requestScope.status}</span>
    </div>
</div>
</body>
</html>
