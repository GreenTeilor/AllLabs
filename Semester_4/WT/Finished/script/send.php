<?php
require 'phpmailer/PHPMailer.php';
require 'phpmailer/SMTP.php';
require 'phpmailer/Exception.php';

function sendEmail($data) {
    if (!error_get_last()) {
        $email = $data['email']['value'];
        $text = "С нашими головоломками вам никогда не будет скучно!";
        
        $title = "Поздравляем с регистрацией на сайте pornhub.com!!!";
        $body = "
        <h2>Благодарим за регистрацию на pornhub.com!</h2>
        <b>Имя:</b> Пользователь сайта pornhub.com<br>
        <b>Почта:</b> $email<br><br>
        <b>Сообщение:</b><br>$text
        ";
        
        $mail = new PHPMailer\PHPMailer\PHPMailer();
        
        $mail->isSMTP();   
        $mail->CharSet = "UTF-8";
        $mail->SMTPAuth   = true;
        $mail->Debugoutput = function($str, $level) {$GLOBALS['data']['debug'][] = $str;};
        
        $mail->Host       = 'smtp.gmail.com'; //Server-address
        $mail->Username   = 'ksistest23@gmail.com'; //Sender login
        $mail->Password   = 'ojlgsezhurunsvlr'; //Session password
        $mail->SMTPSecure = 'ssl';
        $mail->Port       = 465;
        $mail->setFrom('ksistest23@gmail.com', 'Mindbreakers'); // Адрес самой почты и имя отправителя
        
        //Receiver
        $mail->addAddress($email);  
    
        //Send mail
        $mail->isHTML(true);
        $mail->Subject = $title;
        $mail->Body = $body;    
        
        // Проверяем отправленность сообщения
        $mail->send();
        //    echo "nice";    
        //} else {  
        //    echo "bad";
        //}
        
    } else {
        echo "so bad";
    }
}

?>