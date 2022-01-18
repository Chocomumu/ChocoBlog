## 连接数据库
```shell
mysql -hlocalhost -P3306 -uroot -p
```
mysql -h\[ \]\(主机\) -P\[ \]\(端口\) -u\[ \]\(用户\) -p\[密码\]  
-h host MySQL服务器地址  
-P port MySQL服务器端口  
-u user MySQL用户名
-p password MySQL用户名对应密码

## 显示服务器中的数据库
show databases;

## 进入/切换到数据库
use {database_name};

## 显示目前所在数据库
select database();

## 显示目前数据库中的表
show tables;

## 显示database_name数据库中的表
show tables from {database_name};

## 显示MySQL服务器版本
### linux或者windows shell中
mysql --version  
mysql -V
### mysql命令行中
select version();

## 显示表结构
desc {表名};

