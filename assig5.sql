-- Named PL/SQL Block: 
-- PL/SQL Stored Procedure and Stored Function.
-- Write a Stored Procedure namely proc_Grade for the
-- categorization of student. If marks scored by students in
-- examination is <=1500 and marks>=990 then student will be
-- placed in distinction category if marks scored are between
-- 989 and900 category is first class, if marks 899 and 825
-- category is Higher Second Class.
-- Write a PL/SQLblock to use procedure created with above requirement 
-- Stud_Marks(name, total_marks)
-- Result(Roll,Name, Class)

CREATE TABLE Stud_Marks(RollNo INT PRIMARY KEY, Sname VARCHAR(20), Total_Marks INT );
CREATE TABLE Result(RollNo INT REFERENCES Stud_Marks(RollNo), Sname VARCHAR(20), Marks INT, Grade VARCHAR(20) );

INSERT INTO Stud_Marks VALUES
(1, 'Vidyut', 995),
(2, 'Pratap', 828),
(3, 'Kailash', 945),
(4, 'Mukund', 1500),
(5, 'Girish', 900),
(6, 'Neeraj', 850),
(7, 'Prashant', 800),
(8, 'Raj', 899),
(9, 'Hari', 1300),
(10, 'Aditya', 920);

CREATE PROCEDURE proc_Grade(IN SRollNo INT)
BEGIN
   DECLARE Student_Name VARCHAR(20);
   DECLARE Student_Marks VARCHAR(20);
   DECLARE Student_Grade VARCHAR(20);
   DECLARE EXIT HANDLER FOR NOT FOUND SELECT 'NO STUDENT RECORD FOUND' AS 'ERROR';
   SELECT Sname, Total_Marks INTO Student_Name, Student_Marks FROM Stud_Marks WHERE RollNo = SRollNo;
   IF Student_Marks >= 990 THEN
      SET Student_Grade = 'Distinction';
   ELSEIF Student_Marks >= 900 THEN
      SET Student_Grade = 'First Class';
   ELSEIF Student_Marks >= 825 THEN
      SET Student_Grade = 'higher second class';
   END IF;
   INSERT INTO Result VALUES(SRollNo, Student_Name, Student_Marks, Student_Grade);
END;
//

CREATE OR REPLACE FUNCTION fun(student_marks INT)
RETURNS VARCHAR(20)
DETERMINISTIC
BEGIN
   DECLARE Student_Grade VARCHAR(20) DEFAULT 'Pass';
   IF student_marks > 990 THEN
      SET Student_Grade = 'Distinction';
   ELSEIF student_marks >= 900 THEN
      SET Student_Grade = 'First Class';
   ELSEIF student_marks >= 825 THEN
      SET Student_Grade = 'Higher Second Class';
   END IF;
   RETURN Student_Grade;
END;
//
-- calling function 
SELECT RollNo, Sname, Total_Marks, fun_Grade1(Total_Marks) AS GRADE  FROM Stud_marks ORDER BY RollNo;