-- Database Trigger (All Types: Row level and Statement
-- level triggers, Before and After Triggers). Write a
-- database trigger on Library table. The System should keep
-- track of the records that are being updated or deleted. The
-- old value of updated or deleted records should be added in
-- Library_Audit table.
-- Frame problem statement for writing Database
-- Triggers of all types, inline with above statement. The
-- problem statement should clearly state the
-- requirements.

CREATE TABLE Library_Audit (
   old_name VARCHAR(50),
   new_name VARCHAR(50),
   old_price INT,
   new_price INT,
   author VARCHAR(20),
   status VARCHAR(20),
   date TIMESTAMP
);

delimiter //

CREATE OR REPLACE TRIGGER update_book
   AFTER UPDATE ON Book
   FOR EACH ROW
BEGIN
   INSERT INTO Library_Audit 
   SET old_name = old.name, 
       new_name = new.name,
       old_price = old.price, 
       new_price = new.price,
       author = old.author, 
       status = 'Update', 
       date = CURRENT_TIMESTAMP();
END;
//
