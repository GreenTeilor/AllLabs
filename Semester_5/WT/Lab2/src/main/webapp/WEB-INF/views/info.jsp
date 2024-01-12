<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<div class="container-fluid">
  <div class="row">
    <div class="col-sm-3" style="text-align: left; font-size: 1.5rem;">
      Имя: ${sessionScope.user.getName()}
    </div>
    <div class="col-sm-3" style="text-align: left; font-size: 1.5rem;">
      Фамилия: ${sessionScope.user.getLastName()}
    </div>
    <div class="balance col-sm-6" style="text-align: left; font-size: 1.5rem;">
      Баланс: <fmt:formatNumber value="${sessionScope.user.getBalance()}"
                                type="currency"/>
    </div>
  </div>
</div>
