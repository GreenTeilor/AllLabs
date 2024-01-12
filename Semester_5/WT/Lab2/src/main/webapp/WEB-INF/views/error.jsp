<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
    <title>Ошибка</title>
    <link href="<c:url value="/style/common.css"/>" rel="stylesheet">
</head>
<body>
<div style="font-size: 5rem; text-align: center;">
    К сожалению, что-то пошло не так...
</div>
<div style="text-align: center;">
    <img alt="error-image" src="<c:url value="/assets/sadEmoji.png"/>" style="width: 500px;
                                               height: 500px;">
    <c:set var="responseCode" value="${requestScope['jakarta.servlet.error.status_code']}"/>
            <div style="font-size: 4rem;">Код ошибки: ${responseCode}</div>
            <div style="font-size: 4rem;">Сообщение: ${requestScope["jakarta.servlet.error.message"]}</div>
</div>
</body>
</html>