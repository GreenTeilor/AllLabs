<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Проверка быстродействия</title>
</head>
<body>
<div>
    Чтение всех категорий заняло: ${categoriesReadResult}
</div>
<div>
    Чтение всех продуктов заняло: ${productsReadResult}
</div>
<div>
    Нахождение продукта по id заняло: ${productFindResult}
</div>
<div>
    Нахождение продуктов по ключевым словам заняло: ${productsFindResult}
</div>
<div>
    Нахождение пользователя по email заняло: ${userFindResult}
</div>
</body>
</html>
