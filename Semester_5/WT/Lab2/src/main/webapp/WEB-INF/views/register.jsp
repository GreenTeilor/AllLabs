<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jstl/core" %>

<html>
<head>
    <title>Register</title>
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
        Регистрация
    </div>
    <form class="p-3 mt-3 js-form" method="POST" action="<c:url value="/registration"/>">
        <div class="form-field d-flex align-items-center">
            <label for="name"></label><input type="text" class="js-input" name="name" id="name" placeholder="Имя">
        </div>
        <div class="errorInput">${requestScope.nameError}</div>
        <div class="form-field d-flex align-items-center">
            <label for="lastName"></label><input type="text" class="js-input" name="lastName" id="lastName" placeholder="Фамилия">
        </div>
        <div class="errorInput">${requestScope.lastNameError}</div>
        <div class="form-field d-flex align-items-center">
            <label for="email"></label><input type="email" class="js-input" name="email" id="email" placeholder="Email">
        </div>
        <div class="errorInput">${requestScope.emailError}</div>
        <div class="form-field d-flex align-items-center">
            <label for="password"></label><input type="password" class="js-input" name="password" id="password" placeholder="Пароль">
        </div>
        <div class="errorInput">${requestScope.passwordError}</div>
        <div class="form-field d-flex align-items-center">
            <label for="birthDate"></label><input type="text" class="js-input" name="birthDate" id="birthDate" placeholder="Дата рождения" onfocus="(this.type='date')">
        </div>
        <div class="errorInput">${requestScope.birthDateError}</div>
        <button type="submit" class="btn mt-3">Зарегистрироваться</button>
    </form>
    <div class="text-center fs-6">
        <span style="color: black">Есть аккаунт?</span> <a href="<c:url value="/login"/>">Войти</a>
    </div>
    <div class="text-center fs-6">
        <span style="color:${requestScope.color};" class="status">${requestScope.status}</span>
    </div>
</div>
<script src="<c:url value="/script/validator.js"/>"></script>
</body>
</html>