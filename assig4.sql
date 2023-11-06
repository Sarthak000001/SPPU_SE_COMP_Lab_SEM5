create table Borrower(Roll_No int, Name varchar(20), DateOfIssue date, NameOfBook varchar(20), Status varchar(20));
create table Fine(Roll_No int, Curr_Date date, Amt int); 

insert into Borrower values(31120, "Rohan",  "2022/08/23", "MySQL", "Issue"),
(31137, "Rohit",  "2022/07/22", "TOC", "Issue"),
(31168, "Rutya",  "2022/06/22", "DS", "Issue"),
(41126, "Dinya",  "2022/08/02", "DBMS", "Issue"),
(31189, "Tanmya",  "2022/08/22", "LP1", "Issue"),
(11126, "Bhaloo",  "2022/07/22", "BOOK", "Issue"),
(21126, "Cherya",  "2022/06/22", "LOTR", "Issue");

delimiter //
create or replace procedure submit_book(in roll_no int, in BookName varchar(20),out rem int)
begin
	DECLARE days int;
	DECLARE CONTINUE HANDLER FOR NOT FOUND select 'Not Found' as 'Error';
	select DATEDIFF(CURRENT_DATE, DateOfIssue) into days from Borrower where Roll_No=roll_no and NameOfBook=BookName;
    set rem = days;
	IF days > 15 and days < 30 THEN
	insert into Fine values(roll_no, CURRENT_DATE, (days-15)*5);
	ELSEIF days > 30 THEN
	insert into Fine values(roll_no, CURRENT_DATE, (days-30)*50 + 15*5);
	END IF;
	UPDATE Borrower set Status = "R" where Roll_No=roll_no and NameOfBook=BookName;
end;//