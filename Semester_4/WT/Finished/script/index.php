<?php
require_once __DIR__ . '/incs/db.php';

$dataArray = fetchFromDB();
$products = generateCode($dataArray);


$main_template = file_get_contents("../index.html");

$main_template= str_replace(
	'{header}', 
	file_get_contents('../html/header.html'), 
	$main_template);

$main_template= str_replace(
	'{footer}', 
	file_get_contents('../html/footer.html'), 
	$main_template);

$main_template= str_replace(
	'{products}', 
	$products, 
	$main_template);

//$main_template= str_replace("{title}", $title, $main_template);
//$main_template= str_replace("{other_attributes}", $other_attributes, $main_template);
//$main_template= str_replace("{stylesheets_addings}", $stylesheets_addings, $main_template);
//$main_template= str_replace("{js_modules_addings}", $js_modules_addings, $main_template);

//$main_template= str_replace("{left_content}", $left_content, $main_template);
//$main_template= str_replace("{main_content}", $main_content, $main_template);
echo $main_template;