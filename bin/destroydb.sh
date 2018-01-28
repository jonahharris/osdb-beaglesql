#!/bin/sh
echo "\\o $1" >$BG_DATA/$1/sys_db.sql
echo "delete from sys_db where sys_db_name = '$1'" >>$BG_DATA/$1/sys_db.sql
echo "\\q" >>$BG_DATA/$1/sys_db.sql
$BG_PATH/isql <$BG_DATA/$1/sys_db.sql >/dev/null
rm $BG_DATA/$1/*
rmdir $BG_DATA/$1
echo "done."
