<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>Login</title>
    <jsp:include page="dependencies.jsp"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="style/login_register.css" rel="stylesheet">
</head>
<body>
<div class="wrapper">
    <div class="logo">
        <img src="assets/books.png" alt="">
    </div>
    <div class="text-center mt-4 name">
        Вход
    </div>
    <form class="p-3 mt-3" method="POST" action="<c:url value="/login"/>">
        <div class="form-field d-flex align-items-center">
            <input type="email" name="email" id="email" placeholder="Email">
        </div>
        <div class="errorInput">${emailError}</div>
        <div class="form-field d-flex align-items-center">
            <input type="password" name="password" id="password" placeholder="Пароль">
        </div>
        <div class="errorInput">${passwordError}</div>
        <button type="submit" class="btn mt-3">Войти</button>
    </form>
    <div class="text-center fs-6">
        <span style="color: black">Нет аккаунта?</span> <a href="<c:url value="/register"/>">Зарегистрироваться</a>
    </div>
    <div class="text-center fs-6">
        <span class="status">${status}</span>
    </div>
</div>
</body>
</html>
