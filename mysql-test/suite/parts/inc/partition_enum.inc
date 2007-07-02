--disable_query_log
# DATA DIRECTORY
eval SET @data_dir = 'DATA DIRECTORY =
''/tmp''';
let $data_directory = `select @data_dir`;

#INDEX DIRECTORY
eval SET @indx_dir = 'INDEX DIRECTORY =
''/tmp''';
let $index_directory = `select @indx_dir`;
--enable_query_log

eval create table t1 (a enum('A','B','C','D','E','F','G','H','I','J','K','L') not null, primary key(a)) engine=$engine 
partition by key (a) (
partition pa1 $data_directory $index_directory max_rows=20 min_rows=2,
partition pa2 $data_directory $index_directory max_rows=30 min_rows=3,
partition pa3 $data_directory $index_directory max_rows=30 min_rows=4,
partition pa4 $data_directory $index_directory max_rows=40 min_rows=2);
show create table t1;
insert into t1 values ('A'),('D'),('L'),('G');
select * from t1;
select * from t1 where a='A';
update t1 set a='E' where a='L';
select * from t1;
delete from t1 where a='E';
select * from t1;
drop table t1;

eval create table t2 (a enum (
'1','2','3','4','5','6','7','8','9','0',
'A','B','C','D','E','F','G','H','I','J','K','L',
'M','N','O','P','Q','R','S','T','U','V','W','X',
'Y','Z'
) not null, primary key(a)) engine=$engine 
partition by key (a) partitions 27;
show create table t2;
let $letter=26;
--echo $count inserts;
#--disable_query_log
while ($letter)
{
eval insert into t2 values (char(ascii('A')+$letter));
dec $letter;
}
insert into t2 values ('1'),('2'),('3'),('4'),('5'),('6'),('7'),('8'),('9'),('0');
select count(*) from t2;
select * from t2;
drop table t2;

eval create table t3 (a enum (
'1','2','3','4','5','6','7','8','9','0',
'A','B','C','D','E','F','G','H','I','J','K','L',
'M','N','O','P','Q','R','S','T','U','V','W','X',
'Y','Z'
) not null, primary key(a)) engine=$engine 
partition by range (cast(a as unsigned)) subpartition by key (a) subpartitions 3 (
partition pa9 values less than (10),
partition pa18 values less than (19),
partition pa27 values less than (28),
partition pa36 values less than (37)
);
show create table t3;
let $letter=36;
--echo $count inserts;
#--disable_query_log
while ($letter)
{
#eval insert into t3 values ($letter);
dec $letter;
}
select count(*) from t3;
select * from t3;
drop table t3;

eval create table t4 (a enum (
'1','2','3','4','5','6','7','8','9','0',
'A','B','C','D','E','F','G','H','I','J','K','L',
'M','N','O','P','Q','R','S','T','U','V','W','X',
'Y','Z'
) not null, primary key(a)) engine=$engine 
partition by list (cast(a as unsigned)) subpartition by key (a) subpartitions 3 (
partition pa9 values in (1,2,3,4,5,6,7,8,9),
partition pa18 values in (10,11,12,13,14,15,16,17,18),
partition pa27 values in (19,20,21,22,23,24,25,26,27),
partition pa36 values in (28,29,30,31,32,33,34,35,36)
);
show create table t4;
let $letter=36;
--echo $count inserts;
#--disable_query_log
while ($letter)
{
#eval insert into t4 values ($letter);
dec $letter;
}
select count(*) from t4;
select * from t4;
drop table t4;
