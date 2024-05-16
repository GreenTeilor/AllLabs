INSERT INTO `categories` (`name`, `imagePath`) VALUES ('Фантастика', 'assets/fiction.jpg');
INSERT INTO `categories` (`name`, `imagePath`) VALUES ('Исторический', 'assets/historical.jpg');
INSERT INTO `categories` (`name`, `imagePath`) VALUES ('Фэнтези', 'assets/fantasy.jpeg');



INSERT INTO `authors` (`name`) VALUES ('Жюль Верн');
INSERT INTO `authors` (`name`) VALUES ('Роберт Грейвс');
INSERT INTO `authors` (`name`) VALUES ('Анджей Сапковский');
INSERT INTO `authors` (`name`) VALUES ('Джон Толкин');
INSERT INTO `authors` (`name`) VALUES ('Рэй Брэдбери');
INSERT INTO `authors` (`name`) VALUES ('Джордж Оруэлл');
INSERT INTO `authors` (`name`) VALUES ('Лев Толстой');



INSERT INTO `publishers` (`name`) VALUES ('Эксмо');
INSERT INTO `publishers` (`name`) VALUES ('Триумф');
INSERT INTO `publishers` (`name`) VALUES ('Феникс');
INSERT INTO `publishers` (`name`) VALUES ('Проспект');



INSERT INTO `products` (`name`, `description`, `category`, `price`, `author`, `publisher`) VALUES ('Двадцать тысяч лье под водой', 'Роман повествует о приключениях капитана Немо на построенной им подводной лодке «Наутилус» — технологическом чуде описываемого времени. Рассказ ведётся от первого лица, со слов профессора Музея естественной истории Пьера Аронакса, одного из случайных пассажиров этой субмарины.', 'Фантастика', 5.99, 1, 1);
INSERT INTO `products` (`name`, `description`, `category`, `price`, `author`, `publisher`) VALUES ('Я, Клавдий', 'Больному, уродливому юноше Клавдию напророчили стать важнейшим человеком в Римской империи. Только никто не поверил в это предсказание и не обратил внимания на невысокого, искорёженного недугами Клавдия, который и сам предпочитал оставаться в тени...', 'Исторический', 4.50, 2, 1);
INSERT INTO `products` (`name`, `description`, `category`, `price`, `author`, `publisher`) VALUES ('Последнее желание', 'Ведьмак - это мастер меча и мэтр волшебства, ведущий непрерывную войну с кровожадными монстрами, которые угрожают покою сказочной страны. "Ведьмак" - это мир на острие меча, ошеломляющее действие, незабываемые ситуации, великолепные боевые сцены.', 'Фэнтези', 6.99, 3, 2);
INSERT INTO `products` (`name`, `description`, `category`, `price`, `author`, `publisher`) VALUES ('Меч предназначения', 'Cборник рассказов писателя Анджея Сапковского в жанре фэнтези, объединённых общим персонажем — ведьмаком Геральтом из Ривии. Это второе произведение из цикла «Ведьмак» как по хронологии, так и по времени написания. В этой части Геральт впервые встречает Цири и находит своё Предназначение.', 'Фэнтези', 6.49, 3, 2);
INSERT INTO `products` (`name`, `description`, `category`, `price`, `author`, `publisher`) VALUES ('Хоббит, или Туда и Обратно', 'Именно с этой книги начинается знакомство с чудесным миром Средиземья. Но величественная трилогия о Кольце Всевластья случится чуть позже, а сейчас в уютную норку хоббита Бильбо вот-вот постучится Приключение, и он в компании гномов и волшебника Гэндальфа отправится в дальнее путешествие на поиски пропавших сокровищ.', 'Фэнтези', 7.99, 4, 3);
INSERT INTO `products` (`name`, `description`, `category`, `price`, `author`, `publisher`) VALUES ('Властелин колец: Братство Кольца', 'Хоббиту Фродо, племяннику знаменитого Бильбо Бэггинса, доверена важная и опасная миссия — хранить Кольцо Всевластья, которое нужно уничтожить в Огненной Горе, так как, если оно не будет уничтожено, с его помощью Тёмный Властелин Саурон сможет подчинить себе народы Средиземья. Хоббит с друзьями отправляется в полное опасностей путешествие…', 'Фэнтези', 7.35, 4, 3);
INSERT INTO `products` (`name`, `description`, `category`, `price`, `author`, `publisher`) VALUES ('451° по Фаренгейту', '451° по Фаренгейту - температура, при которой воспламеняется и горит бумага. Философская антиутопия Рэя Брэдбери рисует беспросветную картину развития постиндустриального общества; это мир будущего, в котором все письменные издания безжалостно уничтожаются специальным отрядом пожарных, а хранение книг преследуется по закону.', 'Фантастика', 6.44, 5, 3);
INSERT INTO `products` (`name`, `description`, `category`, `price`, `author`, `publisher`) VALUES ('1984', 'Своеобразный антипод второй великой антиутопии XX века "О дивный новый мир" Олдоса Хаксли. Что, в сущности, страшнее: доведенное до абсурда "общество появления" или доведенное до абсолюта "общество идеи"? По Оруэллу, нет и не может быть ничего ужаснее тотальной несвободы...', 'Фантастика', 5.59, 6, 4);
INSERT INTO `products` (`name`, `description`, `category`, `price`, `author`, `publisher`) VALUES ('Война и мир', '"Война и мир" Л. Н. Толстого – книга на все времена. Кажется, что она существовала всегда, настолько знакомым кажется текст, едва мы открываем первые страницы романа, настолько памятны многие его эпизоды: охота и святки, первый бал Наташи Ростовой, лунная ночь в Отрадном, князь Андрей в сражении при Аустерлице...', 'Исторический', 6.89, 7, 4);




INSERT INTO `images` (`path`) VALUES ('assets/JulesVerne_20000LeaguesUnderTheSea1.png');
INSERT INTO `images` (`path`) VALUES ('assets/JulesVerne_20000LeaguesUnderTheSea2.png');
INSERT INTO `images` (`path`) VALUES ('assets/JulesVerne_20000LeaguesUnderTheSea3.png');

INSERT INTO `images` (`path`) VALUES ('assets/RobertGraves_I,Claudius1.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/RobertGraves_I,Claudius2.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/RobertGraves_I,Claudius3.jpg');

INSERT INTO `images` (`path`) VALUES ('assets/AndrzejSapkowski_lastWish1.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/AndrzejSapkowski_lastWish2.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/AndrzejSapkowski_lastWish3.jpg');

INSERT INTO `images` (`path`) VALUES ('assets/AndrzejSapkowski_swordOfDestiny1.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/AndrzejSapkowski_swordOfDestiny2.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/AndrzejSapkowski_swordOfDestiny3.jpg');

INSERT INTO `images` (`path`) VALUES ('assets/JohnTolkien_unexpectedJourney1.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/JohnTolkien_unexpectedJourney2.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/JohnTolkien_unexpectedJourney3.jpg');

INSERT INTO `images` (`path`) VALUES ('assets/JohnTolkien_fellowshipOfRing1.png');
INSERT INTO `images` (`path`) VALUES ('assets/JohnTolkien_fellowshipOfRing2.png');
INSERT INTO `images` (`path`) VALUES ('assets/JohnTolkien_fellowshipOfRing3.png');

INSERT INTO `images` (`path`) VALUES ('assets/RayBradbury_451degreesFarenheit1.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/RayBradbury_451degreesFarenheit2.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/RayBradbury_451degreesFarenheit3.jpg');

INSERT INTO `images` (`path`) VALUES ('assets/GeorgeOrwell_19841.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/GeorgeOrwell_19842.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/GeorgeOrwell_19843.jpg');

INSERT INTO `images` (`path`) VALUES ('assets/LevTolstoy_warAndPeace1.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/LevTolstoy_warAndPeace2.jpg');
INSERT INTO `images` (`path`) VALUES ('assets/LevTolstoy_warAndPeace3.jpg');



INSERT INTO `products_images` (`productId`, `imageId`) VALUES (1, 1);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (1, 2);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (1, 3);

INSERT INTO `products_images` (`productId`, `imageId`) VALUES (2, 4);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (2, 5);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (2, 6);

INSERT INTO `products_images` (`productId`, `imageId`) VALUES (3, 7);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (3, 8);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (3, 9);

INSERT INTO `products_images` (`productId`, `imageId`) VALUES (4, 10);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (4, 11);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (4, 12);

INSERT INTO `products_images` (`productId`, `imageId`) VALUES (5, 13);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (5, 14);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (5, 15);

INSERT INTO `products_images` (`productId`, `imageId`) VALUES (6, 16);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (6, 17);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (6, 18);

INSERT INTO `products_images` (`productId`, `imageId`) VALUES (7, 19);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (7, 20);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (7, 21);

INSERT INTO `products_images` (`productId`, `imageId`) VALUES (8, 22);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (8, 23);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (8, 24);

INSERT INTO `products_images` (`productId`, `imageId`) VALUES (9, 25);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (9, 26);
INSERT INTO `products_images` (`productId`, `imageId`) VALUES (9, 27);



INSERT INTO `labels` (`name`) VALUES ('Бестселлер');
INSERT INTO `labels` (`name`) VALUES ('Фаворит читателей');
INSERT INTO `labels` (`name`) VALUES ('Популярная');
INSERT INTO `labels` (`name`) VALUES ('Захватывающая');
INSERT INTO `labels` (`name`) VALUES ('Поучительная');



INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (1, 1);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (1, 2);

INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (2, 3);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (2, 5);

INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (3, 1);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (3, 2);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (3, 3);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (3, 4);

INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (4, 1);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (4, 2);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (4, 3);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (4, 4);

INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (5, 2);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (5, 3);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (5, 4);

INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (6, 2);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (6, 3);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (6, 4);

INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (7, 2);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (7, 3);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (7, 4);

INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (8, 2);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (8, 3);
INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (8, 5);

INSERT INTO `products_labels` (`productId`, `labelId`) VALUES (9, 5);