-- 1. Создать хранимую процедуру, которая:
-- 		a.	добавляет каждой книге два случайных жанра;
-- 		b.	отменяет совершённые действия, если в процессе работы хотя бы одна операция вставки завершилась ошибкой в силу дублирования значения первичного ключа таблицы «m2m_books_genres» (т.е. у такой книги уже был такой жанр).
CREATE PROCEDURE ADD_RANDOM_GENRES_TO_BOOKS
AS
BEGIN
	DECLARE @BookId INT;
	DECLARE @GenreId INT;
	DECLARE @GenreCount INT;
	DECLARE @InsertSuccess BIT;

	CREATE TABLE #TempGenres (
		BookId INT
		,GenreId INT
		);

	SET XACT_ABORT ON;

	BEGIN TRANSACTION;

	DECLARE book_cursor CURSOR
	FOR
	SELECT b_id
	FROM books;

	OPEN book_cursor;

	FETCH NEXT
	FROM book_cursor
	INTO @BookId;

	WHILE @@FETCH_STATUS = 0
	BEGIN
		DELETE
		FROM #TempGenres;

		SET @GenreCount = 0;

		DECLARE genre_cursor CURSOR
		FOR
		SELECT TOP 2 g_id
		FROM Genres
		ORDER BY NEWID();

		OPEN genre_cursor;

		FETCH NEXT
		FROM genre_cursor
		INTO @GenreId;

		WHILE @@FETCH_STATUS = 0
		BEGIN
			INSERT INTO #TempGenres (
				BookId
				,GenreId
				)
			VALUES (
				@BookId
				,@GenreId
				);

			SET @GenreCount = @GenreCount + 1;

			FETCH NEXT
			FROM genre_cursor
			INTO @GenreId;
		END

		CLOSE genre_cursor;

		DEALLOCATE genre_cursor;

		BEGIN TRY
			INSERT INTO m2m_books_genres (
				b_id
				,g_id
				)
			SELECT BookId
				,GenreId
			FROM #TempGenres;

			SET @InsertSuccess = 1;
		END TRY

		BEGIN CATCH
			SET @InsertSuccess = 0;
		END CATCH;

		IF @InsertSuccess = 0
		BEGIN
			ROLLBACK TRANSACTION;

			CLOSE book_cursor;

			DEALLOCATE book_cursor;

			DROP TABLE #TempGenres;

			RETURN;
		END

		FETCH NEXT
		FROM book_cursor
		INTO @BookId;
	END

	CLOSE book_cursor;

	DEALLOCATE book_cursor;

	COMMIT;

	DROP TABLE #TempGenres;
END

-- 2. Создать хранимую процедуру, которая:
-- 		a.	увеличивает значение поля «b_quantity» для всех книг в два раза;
-- 		b.	отменяет совершённое действие, если по итогу выполнения операции среднее количество экземпляров книг превысит значение 50.
CREATE PROCEDURE DOUBLE_BOOK_QUANTITY
AS
BEGIN
	DECLARE @AverageQuantity FLOAT;

	SET XACT_ABORT ON;

	BEGIN TRANSACTION;

	UPDATE [books]
	SET [b_quantity] = [b_quantity] * 2;

	SELECT @AverageQuantity = AVG([b_quantity] * 1.0) -- Multiply by 1.0 to ensure decimal division
	FROM [books];

	IF @AverageQuantity > 50
	BEGIN
		ROLLBACK TRANSACTION;

		RETURN;
	END

	COMMIT;
END

-- 3. Написать запросы, которые, будучи выполненными параллельно, обеспечивали бы следующий эффект:
-- 		a.	первый запрос должен считать количество выданных на руки и возвращённых в библиотеку книг и не зависеть от запросов на обновление таблицы «subscriptions» (не ждать их завершения);
-- 		b.	второй запрос должен инвертировать значения поля «sb_is_active» таблицы subscriptions с «Y» на «N» и наоборот и не зависеть от первого запроса (не ждать его завершения).

-- a.
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;

BEGIN TRANSACTION;

SELECT COUNT(*) AS [returned_books_amount]
FROM [subscriptions]
WHERE [sb_is_active] = 'N';

COMMIT TRANSACTION;

-- b.
BEGIN TRANSACTION;

UPDATE [subscriptions]
SET [sb_is_active] = CASE 
		WHEN [sb_is_active] = 'Y'
			THEN 'N'
		ELSE 'Y'
		END;

COMMIT TRANSACTION;

-- 4. Написать запросы, которые, будучи выполненными параллельно, обеспечивали бы следующий эффект:
-- 		a.	первый запрос должен считать количество выданных на руки и возвращённых в библиотеку книг;
-- 		b.	второй запрос должен инвертировать значения поля «sb_is_active» таблицы «subscriptions» с «Y» на «N» и наоборот для читателей с нечётными идентификаторами, после чего делать паузу в десять секунд и отменять данное изменение (отменять транзакцию).

--a.
BEGIN TRANSACTION;

SELECT COUNT(*) AS [returned_books_amount]
FROM [subscriptions]
WHERE [sb_is_active] = 'N';

COMMIT TRANSACTION;

--b.
-- SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
-- SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
-- SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
-- SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
BEGIN TRANSACTION;

UPDATE [subscriptions]
SET [sb_is_active] = CASE 
		WHEN [sb_is_active] = 'Y'
			THEN 'N'
		ELSE 'Y'
		END
WHERE [sb_subscriber] % 2 != 0;

WAITFOR DELAY '00:00:10';

ROLLBACK TRANSACTION;

-- 5. Написать код, в котором запрос, инвертирующий значения поля «sb_is_active» 
-- таблицы «subscriptions» с «Y» на «N» и наоборот, будет иметь максимальные шансы 
-- на успешное завершение в случае возникновения ситуации взаимной блокировки с 
-- другими транзакциями.
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SET DEADLOCK_PRIORITY HIGH;

BEGIN TRANSACTION;

UPDATE [subscriptions]
SET [sb_is_active] = CASE 
		WHEN [sb_is_active] = 'Y'
			THEN 'N'
		ELSE 'Y'
		END;

COMMIT TRANSACTION;