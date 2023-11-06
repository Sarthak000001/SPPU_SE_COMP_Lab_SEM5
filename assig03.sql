-- Unnamed PL/SQL code block: Use of Control structure
-- and Exception handling is mandatory
--  Write a PL/SQL block of code for the following requirements:-
-- Schema:
-- 1. Borrower(Roll,Name,DateofIssue, NameofBook, Status)
-- 2. Fine (Roll, Date, Amt)
--  Accept Roll & Name of book from user.
--  Check the number of days (from date of issue), if days
-- are between 15 to 30 then fine amount will be Rs 5 per day.
--  If no. of days>30, per day fine will be Rs 50 per day &
-- for days less than 30, Rs. 5 per day.
--  After submitting the book, status will change from I to R.
--  If condition of fine is true, then details will be stored
-- into fine table
CREATE TABLE IF NOT EXISTS Borrower(
roll_no INT, 
name VARCHAR(40),
issue_date DATE, 
book_name VARCHAR(40),
status CHAR(1)
);

CREATE TABLE IF NOT EXISTS Fine(
roll_no INT, 
paid_date DATE, 
amount INT
);

INSERT INTO Borrower
VALUES
    (1, 'Amit Kumar', '2023-10-15', 'The Great Gatsby', 'I'),
    (2, 'Priya Sharma', '2023-10-16', 'To Kill a Mockingbird', 'I'),
    (3, 'Rahul Verma', '2023-10-17', '1984', 'I'),
    (4, 'Sneha Yadav', '2023-10-18', 'Brave New World', 'I'),
    (5, 'Deepak Singh', '2023-10-19', 'The Catcher in the Rye', 'I'),
    (6, 'Neha Patel', '2023-10-20', 'Lord of the Flies', 'I'),
    (7, 'Poonam Gupta', '2023-10-21', 'The Hobbit', 'I'),
    (8, 'Vikas Sharma', '2023-10-22', 'The Lord of the Rings', 'I');



DELIMITER //
DECLARE
roll_no INT;
book_name VARCHAR(30);
issued_date DATE;
curr_date DATE;
days_diff INT;
fine INT;
roll_no_not_found EXCEPTION;

BEGIN
SET roll_no = 2;
SET book_name = 'To Kill a Mockingbird';
SELECT CURDATE() INTO curr_date;

IF (roll_no NOT IN (SELECT Borrower.roll_no FROM Borrower)) THEN 
	RAISE roll_no_not_found;
END IF ;

SELECT Borrower.issue_date INTO issued_date FROM Borrower WHERE Borrower.roll_no = roll_no;

SET fine = 0 ;
SELECT DATEDIFF(curr_date, issued_date) INTO days_diff;

IF (days_diff <= 30 AND days_diff >= 15) THEN 
      SET fine = days_diff * 5 ;
ELSIF (days_diff > 30) THEN
      SET fine = (days_diff-30)*50 + 30*5;
END IF;

SELECT fine;

UPDATE Borrower SET Borrower.status = 'R' WHERE Borrower.roll_no = roll_no AND Borrower.book_name = book_name ; 

IF fine>0 THEN 
	INSERT INTO Fine SET Fine.roll_no = roll_no, Fine.paid_date = curr_date, Fine.amount = fine ;
END IF ;

EXCEPTION
	WHEN roll_no_not_found THEN 
		SELECT 'Roll no. Not found' AS msg;

END
//



DELIMITER ;

SELECT * FROM Borrower;

SELECT * FROM Fine;

DROP TABLE Borrower;

DROP TABLE Fine;

-- other example 
CREATE TABLE IF NOT EXISTS CircleArea(
sr_no INT UNIQUE KEY AUTO_INCREMENT ,
radius FLOAT, 
Area FLOAT
);


SET SQL_MODE = "ORACLE";

DELIMITER //

DECLARE 
area FLOAT;
pi FLOAT;

BEGIN
SET pi = 3.14 ; 
TRUNCATE TABLE CircleArea;
FOR i IN 5..9 LOOP
  SET area = pi * i * i ;
  INSERT INTO CircleArea SET CircleArea.radius = i, CircleArea.area = area;
END LOOP;

END

//


DELIMITER ;

SELECT * FROM CircleArea;

DROP TABLE CircleArea;