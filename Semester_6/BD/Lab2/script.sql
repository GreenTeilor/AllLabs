-- 3. Показать без повторений идентификаторы книг, которые были взяты читателями.
SELECT DISTINCT [sb_book] AS [book_id]
FROM [dbo].[subscriptions];

-- 7. Показать, сколько читателей брало книги в библиотеке.
SELECT COUNT(*) AS [amount]
FROM [dbo].[subscribers];

-- 11. Показать идентификаторы и даты выдачи книг за первый год работы библиотеки 
-- (первым годом работы библиотеки считать все даты с первой выдачи книги по 31-е 
-- декабря (включительно) того года, когда библиотека начала работать).
SELECT [sb_book]
	,[sb_start]
FROM [subscriptions]
WHERE YEAR([sb_start]) = YEAR((
			SELECT MIN([sb_start])
			FROM [subscriptions]
			));

-- 12. Показать идентификатор одного (любого) читателя, взявшего в библиотеке больше всего книг.
SELECT TOP (1) [sb_subscriber] AS [subscriber_id]
FROM [dbo].[subscriptions]
GROUP BY [sb_subscriber]
ORDER BY COUNT(*) DESC;

-- 15. Показать, сколько в среднем экземпляров книг есть в библиотеке.
SELECT AVG(CAST([b_quantity] AS FLOAT)) AS [avg]
FROM [dbo].[books];