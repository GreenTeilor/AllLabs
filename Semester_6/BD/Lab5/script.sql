-- 1. Создать представление, позволяющее получать список читателей с количеством 
-- находящихся у каждого читателя на руках книг, но отображающее только таких 
-- читателей, по которым имеются задолженности, т.е. на руках у читателя есть хотя 
-- бы одна книга, которую он должен был вернуть до наступления текущей даты.
WITH [have_books]
AS (
	SELECT [s_id]
		,[s_name]
		,COUNT(*) AS [amount]
	FROM [subscribers]
	JOIN [subscriptions] ON [subscribers].[s_id] = [subscriptions].[sb_subscriber]
	WHERE [sb_is_active] = 'Y'
	GROUP BY [s_id]
		,[s_name]
	)
SELECT *
FROM [have_books]
WHERE EXISTS (
		SELECT *
		FROM [subscriptions]
		WHERE [subscriptions].[sb_is_active] = 'Y'
			AND GETDATE() > [sb_finish]
			AND [subscriptions].[sb_subscriber] = [have_books].[s_id]
		);

-- 4. Создать представление, через которое невозможно получить информацию о том, 
-- какая конкретно книга была выдана читателю в любой из выдач.
CREATE
	OR

ALTER VIEW [subscriptions_books_unknown]
	WITH SCHEMABINDING
AS
SELECT [sb_id]
	,[sb_subscriber]
	,[sb_start]
	,[sb_finish]
	,[sb_is_active]
FROM [dbo].[subscriptions];

-- 6. Создать представление, извлекающее информацию о книгах, переводя весь текст в 
-- верхний регистр и при этом допускающее модификацию списка книг.
CREATE
	OR

ALTER VIEW [books_upper_case]
	WITH SCHEMABINDING
AS
SELECT [b_id]
	,UPPER([b_name]) AS [b_name]
	,[b_year]
	,[b_quantity]
FROM [dbo].[books];
GO

CREATE TRIGGER [books_upper_case_ins] ON [books_upper_case]
INSTEAD OF INSERT
AS
SET IDENTITY_INSERT [books] ON;

INSERT INTO [books] (
	[b_id]
	,[b_name]
	,[b_year]
	,[b_quantity]
	)
SELECT (
		CASE 
			WHEN [b_id] IS NULL
				OR [b_id] = 0
				THEN IDENT_CURRENT('books') + IDENT_INCR('books') + ROW_NUMBER() OVER (
						ORDER BY (
								SELECT 1
								)
						) - 1
			ELSE [b_id]
			END
		) AS [b_id]
	,[b_name]
	,[b_year]
	,[b_quantity]
FROM [inserted];

SET IDENTITY_INSERT [books] OFF;
GO

CREATE TRIGGER [books_upper_case_upd] ON [books_upper_case]
INSTEAD OF UPDATE
AS
IF 
	UPDATE ([b_id])

BEGIN
	RAISERROR (
			'UPDATE of Primary Key through
			[books_upper_case_upd]
			view is prohibited.'
			,16
			,1
			);

	ROLLBACK;
END ELSE

UPDATE [books]
SET [books].[b_name] = [inserted].[b_name]
	,[books].[b_year] = [inserted].[b_year]
	,[books].[b_quantity] = [inserted].[b_quantity]
FROM [books]
JOIN [inserted] ON [books].[b_id] = [inserted].[b_id];
GO

-- 8. Создать представление, извлекающее из таблицы m2m_books_authors 
-- человекочитаемую (с названиями книг и именами авторов вместо идентификаторов) 
-- информацию, и при этом позволяющее модифицировать данные в таблице 
-- m2m_books_authors (в случае неуникальности названий книг и имён авторов в обоих 
-- случаях использовать запись с минимальным значением первичного ключа).
CREATE
	OR

ALTER VIEW [books_authors_names]
	WITH SCHEMABINDING
AS
SELECT [b_name] AS [book]
	,[a_name] AS [author]
FROM [dbo].[m2m_books_authors]
JOIN [dbo].[books] ON [dbo].[m2m_books_authors].[b_id] = [dbo].[books].[b_id]
JOIN [dbo].[authors] ON [dbo].[m2m_books_authors].[a_id] = [dbo].[authors].[a_id];
GO

CREATE TRIGGER [books_authors_names_ins] ON [books_authors_names]
INSTEAD OF INSERT
AS
IF EXISTS (
		SELECT *
		FROM [inserted]
		LEFT JOIN [books] ON [inserted].[book] = [books].[b_name]
		LEFT JOIN [authors] ON [inserted].[author] = [authors].[a_name]
		WHERE [b_id] IS NULL
			OR [a_id] IS NULL
		)
BEGIN
	RAISERROR (
			'No identifier for [book] or [author] found'
			,16
			,1
			);

	ROLLBACK;
END
ELSE
BEGIN
	WITH [books_authors]
	AS (
		SELECT MIN(b_id) AS [b_id]
			,MIN(a_id) AS [a_id]
		FROM [inserted]
		JOIN [books] ON [inserted].[book] = [books].[b_name]
		JOIN [authors] ON [inserted].[author] = [authors].[a_name]
		GROUP BY [author]
			,[book]
		)
	INSERT INTO [m2m_books_authors] (
		[b_id]
		,[a_id]
		)
	SELECT [b_id]
		,[a_id]
	FROM [books_authors];
END
GO

CREATE TRIGGER [books_authors_names_del] ON [books_authors_names]
INSTEAD OF DELETE
AS
WITH [books_authors]
AS (
	SELECT MIN(b_id) AS [b_id]
		,MIN(a_id) AS [a_id]
	FROM [deleted]
	JOIN [books] ON [deleted].[book] = [books].[b_name]
	JOIN [authors] ON [deleted].[author] = [authors].[a_name]
	GROUP BY [author]
		,[book]
	)
DELETE
FROM [m2m_books_authors]
WHERE EXISTS (
		SELECT *
		FROM [books_authors]
		WHERE [m2m_books_authors].[b_id] = [books_authors].[b_id]
			AND [m2m_books_authors].[a_id] = [books_authors].[a_id]
		);
GO

-- 14. Создать триггер, не позволяющий выдать книгу читателю, у которого на руках 
-- находится пять и более книг, при условии, что суммарное время, оставшееся до возврата 
-- всех выданных ему книг, составляет менее одного месяца.
CREATE TRIGGER [subscriptions_too_many_books_constraint] ON [subscriptions]
INSTEAD OF INSERT
AS
IF (
		EXISTS (
			SELECT [sb_subscriber]
			FROM [inserted]
			WHERE [sb_subscriber] IN (
					SELECT [sb_subscriber]
					FROM (
						SELECT *
						FROM [subscriptions]
						WHERE [sb_is_active] = 'Y'
						) AS [holders]
					GROUP BY [sb_subscriber]
					HAVING
						-- Здесь вместо MIN по условию должно быть MAX по идее, но мне это показалось странным, 
						-- так как в таком случае можно сломать систему: читатель просто подписывается на книгу и срок истечения просит побольше,
						-- (хоть 2100 год), тогда потом он сможет брать сколько хочет книг и суммарное время, оставшееся до возврата ВСЕХ выданных
						-- ему книг будет все время менее одного месяца, так как всегда будет эта самая подписка, которая истечет очень нескоро.
						-- В моем же варианте проверяется ближайшая истекающая подписка и если осталось < 30 дней, то больше 5 книг взять нельзя
						MIN(DATEDIFF(day, GETDATE(), [sb_finish])) < 30
						AND COUNT(*) > 4
					)
			)
		)
BEGIN
	RAISERROR (
			'No more subscription available for debtor'
			,16
			,1
			);

	ROLLBACK;
END;
ELSE
BEGIN
	SET IDENTITY_INSERT [subscriptions] ON;

	INSERT INTO [subscriptions] (
		[sb_id]
		,[sb_subscriber]
		,[sb_book]
		,[sb_start]
		,[sb_finish]
		,[sb_is_active]
		)
	SELECT (
			CASE 
				WHEN [sb_id] IS NULL
					OR [sb_id] = 0
					THEN IDENT_CURRENT('subscriptions') + IDENT_INCR('subscriptions') + ROW_NUMBER() OVER (
							ORDER BY (
									SELECT 1
									)
							) - 1
				ELSE [sb_id]
				END
			) AS [sb_id]
		,[sb_subscriber]
		,[sb_book]
		,[sb_start]
		,[sb_finish]
		,[sb_is_active]
	FROM [inserted];

	SET IDENTITY_INSERT [subscriptions] OFF;
END;