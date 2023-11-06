-- Cursors: (All types: Implicit, Explicit, Cursor FOR Loop,
-- Parameterized Cursor)
-- Write a PL/SQL block of code using parameterized Cursor, that will
-- merge the data available in the newly created table
-- N_EmpId with the data available in the table O_EmpId.
-- If the data in the first table already exist in the second table then
-- that data should be skipped.

create table Employee(Emp_id int, Name varchar(20), Salary int);
create table NEW_EMPLOYEE(Emp_id int, Name varchar(20), Salary int);

INSERT INTO Employee VALUES (1, "Samarth", 1000), (2, "Sarthak", 1100), (3, "Somesh", 1200);

delimiter //

create or replace procedure addnewdata(in empid int,out raw_count int)
    begin
        declare empid_2 int;
        declare exit_loop boolean;
        declare c1 cursor for select Emp_id from Employee where Emp_id = empid;
        declare continue handler for not found set exit_loop = TRUE;
    open c1;
    emp_loop:LOOP
    fetch c1 into empid_2;
    if not exists (select * from NEW_EMPLOYEE where Emp_id = empid_2) then
     insert into NEW_EMPLOYEE select * from Employee WHERE Emp_id = empid_2;
    end if;
    if exit_loop then
    close c1;
    leave emp_loop;
    end if;
    end LOOP emp_loop;
    select * from NEW_EMPLOYEE;
    select count(*) into raw_count from NEW_EMPLOYEE;
    end;//