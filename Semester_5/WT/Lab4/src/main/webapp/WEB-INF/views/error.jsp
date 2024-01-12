<%@ page contentType="text/html;charset=UTF-8" language="java" %>
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
    <img src="<c:url value="/assets/sadEmoji.png"/>" style="width: 500px;
                                               height: 500px;">
    <c:set var="responseCode" value="${requestScope['jakarta.servlet.error.status_code']}"/>
    <c:choose>
        <c:when test="${responseCode < 200 || responseCode > 300}">
            <div style="font-size: 4rem;">Код ошибки: ${responseCode}</div>
        </c:when>
        <c:otherwise>
            <div style="font-size: 4rem;">Сообщение: ${info}</div>
        </c:otherwise>
    </c:choose>
</div>
</body>
</html>
