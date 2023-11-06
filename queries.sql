-- To change column name 
alter table table_name 
change old_col_name new_col_name data_type
e.g.
alter table dept change Dept Dept_id int;

-- To delete Column from table 
alter table your_table drop column col_to_delete
e.g.
 alter table Dept drop column DeptId;

-- Modify the existing column to be an auto-increment index
ALTER TABLE your_table_name
MODIFY COLUMN Dept_id INT AUTO_INCREMENT PRIMARY KEY;
e.g.
alter table Dept modify column Dept_id int auto_increment primary key;

-- Rename table 
 RENAME TABLE tbl_name TO new_tbl_name
 e.g.
  RENAME TABLE stud TO student ;