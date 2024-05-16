-- 15. Показать всех авторов и количество книг (не экземпляров книг, а «книг как изданий») 
-- по каждому автору.
SELECT [authors].[a_name] AS [name]
	,COUNT(*) AS [books_amount]
FROM [m2m_books_authors]
JOIN [authors] ON [authors].[a_id] = [m2m_books_authors].[a_id]
GROUP BY [authors].[a_id]
	,[authors].[a_name];

-- 16. Показать всех читателей, не вернувших книги, и количество невозвращённых книг по каждому такому читателю.
WITH [not_returned]
AS (
	SELECT *
	FROM [subscriptions]
	WHERE sb_is_active = 'Y'
		AND GETDATE() > sb_finish
	)
SELECT [s_name] AS [name]
	,COUNT(*) AS [amount]
FROM [not_returned]
JOIN [subscribers] ON [not_returned].[sb_subscriber] = [subscribers].[s_id]
GROUP BY [s_id]
	,[s_name];

-- 17. Показать читаемость жанров, т.е. все жанры и то количество раз, которое книги этих
-- жанров были взяты читателями.
SELECT [genres].[g_name] AS [genre]
	,COUNT([m2m_books_genres].[b_id]) AS [amount]
FROM [m2m_books_genres]
JOIN [books] ON [m2m_books_genres].[b_id] = [books].[b_id]
JOIN [subscriptions] ON [m2m_books_genres].[b_id] = [subscriptions].[sb_book]
RIGHT OUTER JOIN [genres] ON [m2m_books_genres].[g_id] = [genres].[g_id]
GROUP BY [genres].[g_id]
	,[genres].[g_name];

-- 18. Показать самый читаемый жанр, т.е. жанр (или жанры, если их несколько), 
-- относящиеся к которому книги читатели брали чаще всего.
WITH [genres_popularity]
AS (
	SELECT [genres].[g_name] AS [genre]
		,COUNT([m2m_books_genres].[b_id]) AS [amount]
	FROM [m2m_books_genres]
	JOIN [books] ON [m2m_books_genres].[b_id] = [books].[b_id]
	JOIN [subscriptions] ON [m2m_books_genres].[b_id] = [subscriptions].[sb_book]
	RIGHT OUTER JOIN [genres] ON [m2m_books_genres].[g_id] = [genres].[g_id]
	GROUP BY [genres].[g_id]
		,[genres].[g_name]
	)
SELECT [genre]
FROM [genres_popularity]
WHERE [amount] = (
		SELECT MAX([amount])
		FROM [genres_popularity]
		);

-- 24. Показать читателя (или читателей, если их окажется несколько), дольше всего держащего у себя книгу (учитывать только случаи, когда книга не возвращена).
WITH [debtor]
AS (
	SELECT [s_name] AS [name]
		,MAX(DATEDIFF(day, [sb_start], GETDATE())) AS [days_hold]
	FROM [subscriptions]
	JOIN [subscribers] ON [subscriptions].sb_subscriber = [subscribers].s_id
	WHERE [sb_is_active] = 'Y'
	GROUP BY [s_id]
		,[s_name]
	)
SELECT [name]
FROM [debtor]
WHERE [days_hold] = (
		SELECT MAX([days_hold])
		FROM [debtor]
		);