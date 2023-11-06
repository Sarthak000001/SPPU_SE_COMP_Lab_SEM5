 declare
    rollno int;
    bookname varchar(40);
    dateofissue date;
    curr_date date;
    rollno_not_found EXCEPTION;
    days_diff int;
    fine int;
    begin
    set rollno = 2;
    set bookname = 'To Kill a Mockingbird';
    select CURDATE() into curr_date;
    select curr_date;
    if (rollno not in (select Borrower.rollno from Borrower)) then
    raise rollno_not_found;
    end if;
    select Borrower.dateofissue into dateofissue from Borrower where Borrower.rollno=rollno;
    select dateofissue;
    select DATEDIFF(curr_date,dateofissue) into days_diff;
    select days_diff;
    set fine = 0;
    if (days_diff <= 30 AND days_diff >= 15) then
    set fine = days_diff*5;
    elsif (days_diff > 30) then
    set fine = ((days_diff-30)*50) + (30*5);
    end if;
    select fine;
    update Borrower set Borrower.status = "R" where Borrower.rollno=rollno AND Borrower.bookname=bookname;
    if fine > 0 then
    select fine;
    insert into Fine set Fine.rollno=rollno,Fine.paiddate=curr_date,Fine.amount=fine;
    end if;
    EXCEPTION
    when rollno_not_found then
    select "Roll no. not found" AS msg;
    end;//