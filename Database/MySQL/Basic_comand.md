## �������ݿ�
```shell
mysql -hlocalhost -P3306 -uroot -p
```
mysql -h\[ \]\(����\) -P\[ \]\(�˿�\) -u\[ \]\(�û�\) -p\[����\]  
-h host MySQL��������ַ  
-P port MySQL�������˿�  
-u user MySQL�û���
-p password MySQL�û�����Ӧ����

## ��ʾ�������е����ݿ�
show databases;

## ����/�л������ݿ�
use {database_name};

## ��ʾĿǰ�������ݿ�
select database();

## ��ʾĿǰ���ݿ��еı�
show tables;

## ��ʾdatabase_name���ݿ��еı�
show tables from {database_name};

## ��ʾMySQL�������汾
### linux����windows shell��
mysql --version  
mysql -V
### mysql��������
select version();

## ��ʾ��ṹ
desc {����};

