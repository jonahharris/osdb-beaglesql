#!/bin/sh
mkdir $BG_DATA/$1
cp $BG_DATA/template/* $BG_DATA/$1
echo "\\oi" >$BG_DATA/$1/sys_db.sql
echo "insert into sys_db values ('$1')" >>$BG_DATA/$1/sys_db.sql
echo "\\q" >>$BG_DATA/$1/sys_db.sql
$BG_PATH/isql <$BG_DATA/$1/sys_db.sql >/dev/null
echo "done."
