<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<c:set var="user" value="${user}"/>
<div class="container-fluid">
  <div class="row">
    <div class="col-sm-3" style="text-align: left; font-size: 1.5rem;">
      Имя: ${user.getName()}
    </div>
    <div class="col-sm-3" style="text-align: left; font-size: 1.5rem;">
      Фамилия: ${user.getLastName()}
    </div>
    <div class="balance col-sm-6" style="text-align: left; font-size: 1.5rem;">
      Баланс: <fmt:formatNumber value="${user.getBalance()}"
                                type="currency"/>
    </div>
  </div>
</div>
