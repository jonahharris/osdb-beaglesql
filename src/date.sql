create table datetests ( trials DATE )
insert into datetests values ( DATE '02/01/98' )
insert into datetests values ( CURRENT_DATE )
select * from datetests
select  * from datetests where trials > DATE '02/06/98'
select  * from datetests where trials < DATE '02/06/98'
