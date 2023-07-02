<?php

require_once __DIR__ . '/incs/data.php';
require_once __DIR__ . '/incs/functions.php';
require_once __DIR__ . '/send.php';

$registrationLogin_template = file_get_contents("../html/registrationLogin.html");

if (!empty($_POST)){
	//debug($_POST);	
	$fields = load($fields);
	//debug($fields);
	if (preg_match('/\A[a-z0-9]+([-._][a-z0-9]+)*@([a-z0-9]+(-[a-z0-9]+)*\.)+[a-z]{2,4}\z/', $fields['email']['value'])) {
		$registrationLogin_template= str_replace(
			'{status}', 
			'<span style="font-size: 120%; color: green; margin-left: 40%;">Успех!</span>', 
			$registrationLogin_template);
		sendEmail($fields);	
	} else {
		$registrationLogin_template= str_replace(
			'{status}', 
			'<span style="font-size: 120%; color: red; margin-left: 25%;">Невалидный email!</span>', 
			$registrationLogin_template);
	}
} else {
	$registrationLogin_template= str_replace(
		'{status}', 
		'<span></span>', 
		$registrationLogin_template);
}

$registrationLogin_template= str_replace(
	'{header}', 
	file_get_contents('../html/header.html'), 
	$registrationLogin_template);

    $registrationLogin_template= str_replace(
	'{footer}', 
	file_get_contents('../html/footer.html'), 
	$registrationLogin_template);

echo $registrationLogin_template;