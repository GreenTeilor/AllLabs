CREATE DATABASE IF NOT EXISTS `shop_db`;
USE `shop_db`;
CREATE TABLE IF NOT EXISTS `categories` (
	`id` INT PRIMARY KEY AUTO_INCREMENT,
    `name` VARCHAR(50) NOT NULL,
    `imagePath` VARCHAR(50) NOT NULL,
    INDEX `name_indx` (`name`)
);

CREATE TABLE IF NOT EXISTS `users` (
	`id` INT PRIMARY KEY AUTO_INCREMENT,
    `name` VARCHAR(50) NOT NULL,
    `lastName` VARCHAR(50) NOT NULL,
    `email` VARCHAR(90) NOT NULL UNIQUE,
    `birthDate` TIMESTAMP NOT NULL,
    `registrationDate` TIMESTAMP NOT NULL,
    `balance` DECIMAL(26, 2) NOT NULL,
    `password` VARCHAR(64) NOT NULL,
    `address` VARCHAR(90),
    `phoneNumber` VARCHAR(20) 
);

CREATE TABLE IF NOT EXISTS `orders` (
	`id` INT PRIMARY KEY AUTO_INCREMENT,
	`userId` INT NOT NULL,
	`date` TIMESTAMP NOT NULL,
    `price` DECIMAL(24, 2) NOT NULL,
    CONSTRAINT `fk_userId` FOREIGN KEY (`userId`) REFERENCES `users` (`id`),
    INDEX `userId_indx` (`userId`)
);

CREATE TABLE IF NOT EXISTS `products` (
	`id` INT PRIMARY KEY AUTO_INCREMENT,
    `name` VARCHAR(50) NOT NULL,
    `description` VARCHAR(350) NOT NULL,
    `imagePath` VARCHAR(50) NOT NULL,
    `category` VARCHAR(50) NOT NULL,
    `price` DECIMAL(24, 2) NOT NULL,
    CONSTRAINT `fk_category` FOREIGN KEY (`category`) REFERENCES `categories` (`name`),
    INDEX `category_indx` (`category`)
);

CREATE TABLE IF NOT EXISTS `orders_products` (
	`id` INT PRIMARY KEY AUTO_INCREMENT,
    `orderId` INT NOT NULL,
    `productId` INT NOT NULL,
    CONSTRAINT `fk_orderId` FOREIGN KEY (`orderId`) REFERENCES `orders` (`id`),
    CONSTRAINT `fk_productId` FOREIGN KEY (`productId`) REFERENCES `products` (`id`),
    INDEX `orderId_indx` (`orderId`),
    INDEX `productId_indx` (`productId`)
);

/*===TEST DATA===*/

/*CATEGORIES INSERT*/
INSERT INTO `categories` (`name`, `imagePath`) VALUES ('Фантастика', 'assets/fiction.jpg');
INSERT INTO `categories` (`name`, `imagePath`) VALUES ('Исторический', 'assets/historical.jpg');
INSERT INTO `categories` (`name`, `imagePath`) VALUES ('Фэнтези', 'assets/fantasy.jpeg');

/*PRODUCTS INSERT*/
INSERT INTO `products` (`name`, `description`, `imagePath`, `category`, `price`) VALUES ('Двадцать тысяч лье под водой', 
	'Роман повествует о приключениях капитана Немо на построенной им подводной лодке «Наутилус» — технологическом чуде описываемого времени. Рассказ ведётся от первого лица, со слов профессора Музея естественной истории Пьера Аронакса, одного из случайных пассажиров этой субмарины.',
	'assets/JulesVerne_20000LeaguesUnderTheSea.png', 'Фантастика', 5.99);
INSERT INTO `products` (`name`, `description`, `imagePath`, `category`, `price`) VALUES ('Я, Клавдий', 
	'Больному, уродливому юноше Клавдию напророчили стать важнейшим человеком в Римской империи. Только никто не поверил в это предсказание и не обратил внимания на невысокого, искорёженного недугами Клавдия, который и сам предпочитал оставаться в тени...',
	'assets/RobertGraves_I,Claudius.jpg', 'Исторический', 4.50);
INSERT INTO `products` (`name`, `description`, `imagePath`, `category`, `price`) VALUES ('Последнее желание', 
	'Ведьмак - это мастер меча и мэтр волшебства, ведущий непрерывную войну с кровожадными монстрами, которые угрожают покою сказочной страны. "Ведьмак" - это мир на острие меча, ошеломляющее действие, незабываемые ситуации, великолепные боевые сцены.',
	'assets/AndrzejSapkowski_lastWish.jpg', 'Фэнтези', 6.99);
INSERT INTO `products` (`name`, `description`, `imagePath`, `category`, `price`) VALUES ('Меч предназначения', 
	'Cборник рассказов писателя Анджея Сапковского в жанре фэнтези, объединённых общим персонажем — ведьмаком Геральтом из Ривии. Это второе произведение из цикла «Ведьмак» как по хронологии, так и по времени написания. В этой части Геральт впервые встречает Цири и находит своё Предназначение.',
	'assets/AndrzejSapkowski_swordOfDestiny.jpg', 'Фэнтези', 6.49);
INSERT INTO `products` (`name`, `description`, `imagePath`, `category`, `price`) VALUES ('Хоббит, или Туда и Обратно', 
	'Именно с этой книги начинается знакомство с чудесным миром Средиземья. Но величественная трилогия о Кольце Всевластья случится чуть позже, а сейчас в уютную норку хоббита Бильбо вот-вот постучится Приключение, и он в компании гномов и волшебника Гэндальфа отправится в дальнее путешествие на поиски пропавших сокровищ.',
	'assets/JohnTolkien_unexpectedJourney.jpg', 'Фэнтези', 7.99);
INSERT INTO `products` (`name`, `description`, `imagePath`, `category`, `price`) VALUES ('Властелин колец: Братство Кольца', 
	'Хоббиту Фродо, племяннику знаменитого Бильбо Бэггинса, доверена важная и опасная миссия — хранить Кольцо Всевластья, которое нужно уничтожить в Огненной Горе, так как, если оно не будет уничтожено, с его помощью Тёмный Властелин Саурон сможет подчинить себе народы Средиземья. Хоббит с друзьями отправляется в полное опасностей путешествие…',
	'assets/JohnTolkien_fellowshipOfRing.png', 'Фэнтези', 7.35);
INSERT INTO `products` (`name`, `description`, `imagePath`, `category`, `price`) VALUES ('451° по Фаренгейту', 
	'451° по Фаренгейту - температура, при которой воспламеняется и горит бумага. Философская антиутопия Рэя Брэдбери рисует беспросветную картину развития постиндустриального общества; это мир будущего, в котором все письменные издания безжалостно уничтожаются специальным отрядом пожарных, а хранение книг преследуется по закону.',
	'assets/RayBradbury_451degreesFarenheit.jpg', 'Фантастика', 6.44);
INSERT INTO `products` (`name`, `description`, `imagePath`, `category`, `price`) VALUES ('1984', 
	'Своеобразный антипод второй великой антиутопии XX века "О дивный новый мир" Олдоса Хаксли. Что, в сущности, страшнее: доведенное до абсурда "общество появления" или доведенное до абсолюта "общество идеи"? По Оруэллу, нет и не может быть ничего ужаснее тотальной несвободы...',
	'assets/GeorgeOrwell_1984.jpg', 'Фантастика', 5.59);
INSERT INTO `products` (`name`, `description`, `imagePath`, `category`, `price`) VALUES ('Война и мир', 
	'"Война и мир" Л. Н. Толстого – книга на все времена. Кажется, что она существовала всегда, настолько знакомым кажется текст, едва мы открываем первые страницы романа, настолько памятны многие его эпизоды: охота и святки, первый бал Наташи Ростовой, лунная ночь в Отрадном, князь Андрей в сражении при Аустерлице...',
	'assets/LevTolstoy_warAndPeace.jpg', 'Исторический', 6.89);
 