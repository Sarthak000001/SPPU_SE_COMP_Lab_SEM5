-- Drop previous tables 
drop table Employee;
drop table Project;
drop table Dept;

-- creating table 
create table Employee(
    Emp_id int,
    Dept_id int,
    Emp_fname varchar(50),
    Emp_lname varchar(50),
    Emp_position varchar(50),
    Emp_salary decimal(10, 2),
    Emp_joinDate date
);
create table Dept(
    Dept_id int,
    Dept_name varchar(50),
    Dept_location varchar(50)
);
create table Project(
    Proj_id int,
    Dept_id int,
    Proj_Name varchar(50),
    Proj_Location varchar(50),
    Proj_cost decimal(10, 2),
    Proj_year int
);

-- table alteration modify existing column to be an auto-increment index
alter table Dept modify column Dept_id int auto_increment primary key;
alter table Employee modify column Emp_id int auto_increment primary key;
alter table Project modify column Proj_id int auto_increment primary key;

-- adding primary & foreign key constraint 
-- alter table Dept add primary key(Dept_id);
alter table Employee add foreign key(Dept_id) references Dept(Dept_id);
alter table Project add foreign key(Dept_id) references Dept(Dept_id); 

-- Insert into Dept table 
insert into Dept(Dept_name,Dept_location) values
('CE','Mumbai'),
('ENTC','Pune'),
('IT','Bangalore'),
('FE', 'Mumbai');
-- Insert into Employee table 
INSERT INTO Employee (Dept_id, Emp_fname, Emp_lname, Emp_Position, Emp_salary, Emp_JoinDate)
VALUES
    (2, 'Prashant', 'Sharma', 'ASS.', 55000, '2000-03-15'),
    (3, 'Hema', 'Patel', 'STAFF', 48000, '2005-08-20'),
    (1, 'Priti', 'Singh', 'PROF.', 75000, '1998-12-10'),
    (1, 'Harish', 'Verma', 'PROF.', 82000, '2004-06-20'),
    (3, 'Priya', 'Gupta', 'ASS.', 62000, '2008-03-12'),
    (2, 'Rajesh', 'Kumar', 'STAFF', 50000, '2006-09-05'),
    (1, 'Poonam', 'Sinha', 'STAFF', 49000, '2010-11-18'),
    (3, 'Himanshu', 'Shukla', 'PROF.', 78000, '2003-07-25'),
    (1, 'Neha', 'Rajput', 'ASS.', 62000, '2009-12-03'),
    (2, 'Rahul', 'Mehta', 'PROF.', 75000, '2007-04-08');
-- Insert into Project table 
INSERT INTO Project (Dept_id, Proj_Name, Proj_Location, Proj_cost, Proj_year)
VALUES
    (1, 'Cloud Computing Project 1', 'Cloud', 150000, 2004),
    (2, 'Web Development Project 1', 'Web', 90000, 2005),
    (3, 'App Development Project 1', 'Mobile', 110000, 2007),
    (1, 'Blockchain Project 1', 'Blockchain', 250000, 2006),
    (4, 'Machine Learning Project 1', 'AI', 300000, 2007);

--1. Display all Employee details with Department 'Computer' and 'IT' and Employee first name starting with 'p' or 'h'
SELECT * FROM Employee JOIN Dept USING(Dept_id)
WHERE (Dept_name = 'CE' OR Dept_name = 'IT') 
AND (Emp_fname LIKE 'P%' OR Emp_fname LIKE 'H%');

-- 2.Lists the number of different Employee Positions:
SELECT DISTINCT Emp_Position FROM Employee;

-- 3.Give 10% increase in Salary of the Employee whose Birthdate is before 1985:
UPDATE Employee 
SET Emp_salary = Emp_salary * 1.10
WHERE YEAR(Emp_joinDate) < 1985;

-- 4.Delete Department details where the location is 'Mumbai':
DELETE FROM Dept WHERE Dept_location = 'Mumbai';

-- 5.Find the names of Projects with location 'Pune':
SELECT Proj_Name FROM Project WHERE Proj_Location = 'Pune';

-- 6.Find the project having cost in between 100000 to 500000:
SELECT * FROM Project WHERE Proj_cost BETWEEN 100000 AND 500000;

-- 7.Find the project having the maximum price and find the average of Project cost:
SELECT MAX(Proj_cost) AS Max_Project_Cost,
AVG(Proj_cost) AS Avg_Project_Cost FROM Project;

-- 8.Display all employees with Emp_id and Emp name in decreasing order of Emp_lname:
SELECT Emp_id, CONCAT(Emp_fname, ' ', Emp_lname) AS Emp_name
FROM Employee
ORDER BY Emp_lname DESC;

-- 9.Display Proj_name, Proj_location, Proj_cost of all projects started in 2004, 2005, and 2007:
SELECT Proj_Name,Proj_Location,Proj_cost FROM Project
WHERE Proj_year IN (2004,2005,2007);
