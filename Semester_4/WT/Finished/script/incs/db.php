<?php

function fetchFromDB() {
	$dbh = new PDO('mysql:dbname=mindbreakersdatabase;host=127.0.0.1', 'root', 'Tatidavi291173');
	$sth = $dbh->prepare("SELECT * FROM `cards` ORDER BY `name`");
	$sth->execute();
	$array = $sth->fetchAll(PDO::FETCH_ASSOC);
	return $array;
}

function generateCode($dataArray) {
	$gap = chr(13) . chr(10);
	$generatedCode = "";
	foreach ($dataArray as $value) {
		$generatedCode = $generatedCode . "<div class=\"product-item\">" . $gap;
		$generatedCode = $generatedCode . "<img src=\"" . $value['src'] . "\">" . $gap;
		$generatedCode = $generatedCode . "<div class=\"product-list\">" . $gap;
		$generatedCode = $generatedCode . "<h3>" . $value['name'] . "</h3>" . $gap;
		$generatedCode = $generatedCode . "<span class=\"price\">" . $value['price'] . "</span>" . $gap;
		$generatedCode = $generatedCode . "<a href=\"card.php\" class=\"button\">В корзину</a>" . $gap;
		$generatedCode = $generatedCode . "</div>" . $gap . "</div>" . $gap;
	}
	return $generatedCode;
}

