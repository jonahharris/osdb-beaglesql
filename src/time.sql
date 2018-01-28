create table timetests ( trials TIME )
insert into timetests values ( TIME '11:56:14' )
insert into timetests values ( CURRENT_TIME )
select * from timetests
select  * from timetests where trials > TIME '11:58:23'
select  * from timetests where trials < TIME '11:58:23'
