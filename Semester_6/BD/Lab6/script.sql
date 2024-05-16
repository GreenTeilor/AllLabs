-- 1. Создать хранимую функцию, получающую на вход идентификатор читателя и 
-- возвращающую список идентификаторов книг, которые он уже прочитал и вернул в 
-- библиотеку.
CREATE FUNCTION GET_RETURNED_BOOKS (@subscriber_id INT)
RETURNS @returned_books_id TABLE ([b_id] INT)
AS
BEGIN
	INSERT @returned_books_id
	SELECT [sb_book]
	FROM [subscriptions]
	WHERE [sb_subscriber] = @subscriber_id
		AND [sb_is_active] = 'N';

	RETURN
END;
GO

-- 2. Создать хранимую функцию, возвращающую список первого диапазона свободных 
-- значений автоинкрементируемых первичных ключей в указанной таблице 
-- (например, если в таблице есть первичные ключи 1, 4, 8, то первый свободный 
-- диапазон — это значения 2 и 3).
CREATE FUNCTION GET_FIRST_PK_DIAPASON ()
RETURNS @free_keys TABLE (
	[start] INT
	,[stop] INT
	)
AS
BEGIN
	INSERT @free_keys
	SELECT TOP (1) [start]
		,[stop]
	FROM (
		SELECT [min_t].[sb_id] + 1 AS [start]
			,(
				SELECT MIN([sb_id]) - 1
				FROM [subscriptions] AS [x]
				WHERE [x].[sb_id] > [min_t].[sb_id]
				) AS [stop]
		FROM [subscriptions] AS [min_t]
		
		UNION
		
		SELECT 1 AS [start]
			,(
				SELECT MIN([sb_id]) - 1
				FROM [subscriptions] AS [x]
				WHERE [sb_id] > 0
				) AS [stop]
		) AS [data]
	WHERE [stop] >= [start]
	ORDER BY [start]
		,[stop]

	RETURN
END;
GO

-- 3. Создать хранимую функцию, получающую на вход идентификатор читателя и 
-- возвращающую 1, если у читателя на руках сейчас менее десяти книг, и 0 в 
-- противном случае.
CREATE FUNCTION IS_HAVE_LESS_THAN_10_BOOKS (@subscriber_id INT)
RETURNS BIT
AS
BEGIN
	DECLARE @result BIT;
	DECLARE @books_amount SMALLINT;

	SET @books_amount = (
			SELECT count(*)
			FROM [subscriptions]
			WHERE [sb_subscriber] = @subscriber_id
				AND [sb_is_active] = 'Y'
			);

	IF @books_amount < 10
	BEGIN
		SET @result = 1;
	END
	ELSE
	BEGIN
		SET @result = 0;
	END

	RETURN @result;
END;
GO

-- 4. Создать хранимую функцию, получающую на вход год издания книги и 
-- возвращающую 1, если книга издана менее ста лет назад, и 0 в противном случае.
CREATE FUNCTION IS_PUBLISHED_LESS_THAN_100_YEARS_AGO (@year_published SMALLINT)
RETURNS BIT
AS
BEGIN
	DECLARE @result BIT;
	DECLARE @years_ago_published SMALLINT;

	SET @years_ago_published = YEAR(GETDATE()) - @year_published;

	IF @years_ago_published < 100
	BEGIN
		SET @result = 1;
	END
	ELSE
	BEGIN
		SET @result = 0;
	END

	RETURN @result;
END;
GO

-- 9. Создать хранимую процедуру, автоматически создающую и наполняющую данными 
-- таблицу «arrears», в которой должны быть представлены идентификаторы и имена 
-- читателей, у которых до сих пор находится на руках хотя бы одна книга, по которой 
-- дата возврата установлена в прошлом относительно текущей даты.
CREATE PROCEDURE CREATE_ARREARS
AS
BEGIN
	DROP TABLE

	IF EXISTS [arrears];
		CREATE TABLE [arrears] (
			[s_id] INT NOT NULL
			,[s_name] NVARCHAR(150) NOT NULL
			,PRIMARY KEY ([s_id])
			)

	INSERT [arrears]
	SELECT [s_id]
		,[s_name]
	FROM [subscribers]
	JOIN [subscriptions] ON [subscribers].[s_id] = [subscriptions].[sb_subscriber]
	WHERE [sb_is_active] = 'Y'
		AND DATEDIFF(day, GETDATE(), [sb_finish]) < 0
	GROUP BY [s_id]
		,[s_name];
END;
GO

