-- 5. Для всех выдач, произведённых до 1-го января 2012-го года, уменьшить значение дня выдачи на 3.
UPDATE [subscriptions]
SET [sb_start] = DATEADD(day, - 3, [sb_start])
WHERE sb_start < CAST('01-01-2012' AS DATE);

-- 6. Отметить как невозвращённые все выдачи, полученные читателем с идентификатором 2.
UPDATE [subscriptions]
SET [sb_is_active] = N'Y'
WHERE [sb_subscriber] = 2;

-- 7. Удалить информацию обо всех выдачах читателям книги с идентификатором 1.
DELETE
FROM [subscriptions]
WHERE [sb_book] = 1;

-- 8. Удалить все книги, относящиеся к жанру «Классика».
DELETE
FROM [books]
WHERE [b_id] IN (
		SELECT [b_id]
		FROM [genres]
		JOIN [m2m_books_genres] ON [genres].[g_id] = [m2m_books_genres].[g_id]
		WHERE [g_name] = N'Классика'
		);

-- 9. Удалить информацию обо всех выдачах книг, произведённых после 20-го числа любого месяца любого года.
DELETE
FROM [subscriptions]
WHERE DAY(sb_start) > 20;