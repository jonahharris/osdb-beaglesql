; Open database
;
\o test
;
; Create a table called 'phonebook'
;
create table phonebook (name char, addr char, city char, state char, zip char, phone char)
;
; Insert some data into the table
;
insert into phonebook values ('Robert Klein', 'This Street', 'This Town', 'MD', '12345', '555-2354')
insert into phonebook values ('Roberto Alomar', 'This Street', 'Baltimore', 'MD', '12345', '555-2354')
insert into phonebook values ('Cathryn Klein', 'This Street', 'This Town', 'MD', '12345', '555-2354')
insert into phonebook values ('J. Smoltz', 'Peach Street', 'Atlanta', 'GA', '12345', '999-9999')
;
; Create an index for the table
;
create index iphonebook on phonebook using name, addr, city
;
; Insert another value into the table
;
insert into phonebook values ('Michelle Blanchard', 'Long way way', 'BF Egypt', 'EG', '12345', '999-9999')
;
; Create another table called 'birthday'
;
create table birthday (name char, date char)
;
; Insert some data
; 
insert into birthday values ('Robert Klein', '12/11/1968')
insert into birthday values ('Roberto Alomar', '01/21/1996')
insert into birthday values ('Cathryn Klein', '12/25/1996')
insert into birthday values ('Michelle Blanchard', '08/01/1996')
;
; Another table
;
create table chardate (date char, chdate char)
insert into chardate values ('12/11/1968', 'December 11, 1968')
insert into chardate values ('01/21/1996', 'January 21, 1996')
insert into chardate values ('12/25/1996', 'December 25, 1996')
insert into chardate values ('08/01/1996', 'August 1, 1996')
;
; Execute a select joining all three tables an using the index for the
; 'phonebook' table
;
select phonebook.name, chdate, phone from phonebook, birthday, chardate where phonebook.name begins 'R' and phonebook.name = birthday.name and birthday.date = chardate.date using-index iphonebook
;
; Delete a record from the phonebook table
;
delete from phonebook where phonebook.name begins 'Roberto'
;
; Execute the select again, this time without the index
;
select phonebook.name, chdate, phone from phonebook, birthday, chardate where phonebook.name begins 'R' and phonebook.name = birthday.name and birthday.date = chardate.date
;
; show system tables
;
select * from sys_db
select * from sys_table
select * from sys_field
select * from sys_index
select * from sys_user
;
; Drop the tables
;
drop table phonebook
drop table birthday
drop table chardate
;
; Quit
\q
