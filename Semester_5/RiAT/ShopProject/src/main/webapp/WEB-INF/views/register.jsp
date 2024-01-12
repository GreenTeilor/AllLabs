<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Register</title>
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
        Регистрация
    </div>
    <form class="p-3 mt-3 js-form" method="POST" action="register">
        <div class="form-field d-flex align-items-center">
            <input type="text" class="js-input" name="name" id="name" placeholder="Имя">
        </div>
        <div class="errorInput">${nameError}</div>
        <div class="form-field d-flex align-items-center">
            <input type="text" class="js-input" name="lastName" id="lastName" placeholder="Фамилия">
        </div>
        <div class="errorInput">${lastNameError}</div>
        <div class="form-field d-flex align-items-center">
            <input type="email" class="js-input" name="email" id="email" placeholder="Email">
        </div>
        <div class="errorInput">${emailError}</div>
        <div class="form-field d-flex align-items-center">
            <input type="password" class="js-input" name="password" id="password" placeholder="Пароль">
        </div>
        <div class="errorInput">${passwordError}</div>
        <div class="form-field d-flex align-items-center">
            <input type="text" class="js-input" name="birthDate" id="birthDate" placeholder="Дата рождения" onfocus="(this.type='date')">
        </div>
        <div class="errorInput">${birthDateError}</div>
        <button type="submit" class="btn mt-3">Зарегистрироваться</button>
    </form>
    <div class="text-center fs-6">
        <span style="color: black">Есть аккаунт?</span> <a href="login">Войти</a>
    </div>
    <div class="text-center fs-6">
        <span style="color:${color};" class="status">${status}</span>
    </div>
</div>
<script src="script/validator.js"></script>
</body>
</html>