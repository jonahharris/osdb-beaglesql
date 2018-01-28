create table stamptests ( trials TIMESTAMP )
insert into stamptests values ( TIMESTAMP 'Sun Feb 8 11:58:14 CST 1998' )
insert into stamptests values ( CURRENT_TIMESTAMP )
select * from stamptests
select  * from stamptests where trials > TIMESTAMP 'Sun Feb 8 11:56:23 CST 1998'
select  * from stamptests where trials < TIMESTAMP 'SUN Feb 8  11:55:23 CST 1998'
