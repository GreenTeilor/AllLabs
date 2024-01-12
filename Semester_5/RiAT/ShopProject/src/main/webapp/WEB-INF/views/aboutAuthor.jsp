<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>About author</title>
    <jsp:include page="dependencies.jsp"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="style/common.css" rel="stylesheet">
    <link href="style/footer.css" rel="stylesheet">
</head>
<body>
<div class="wrapper">
    <jsp:include page="header.jsp"/>
    <div class="main">
        <div>
            <h1>Обо мне</h1>
        </div>
        <div class="container-fluid">
            <div class="row">
                <img class="col-sm-4" src="assets/me.jpg">
                <div class="col-sm-8">
                    <h2>Вводная</h2>
                    <p>
                        Меня зовут lorem ipsum. 20-летний студент БГУИР. Немного программирую.
                    </p>
                    <h3>Продолжение</h3>
                    <p>
                        Кто я такой?
                    </p>
                    <p>
                        Точно, здесь надо написать о себе.
                    </p>
                </div>
            </div>
        </div>
    </div>
    <jsp:include page="footer.jsp"/>
</div>
</body>
</html>
