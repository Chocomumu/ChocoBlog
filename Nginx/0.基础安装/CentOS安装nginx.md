## 环境基础安装
### 1.（可选）wget版本确定/安装  
安装  
```sh
yum install wget
```
版本查看  
```sh
wget --version
wget -V
```
![wget version](../.pic/wget%20version.png)  

### 2.检查、安装gcc  
(1)检查gcc安装版本
```sh
gcc -v
```
若显示“command not found”，说明gcc未安装；  
使用yum安装gcc  
```sh
yum install gcc
```
### 3.安装PCRE  
查看pcre版本，若不存在则需要安装pcre  
```sh
pcre-config --version
rpm -qa pcre-devel
```
若未安装PCRE，configure时会看到以下错误  
```sh
./configure: error: the HTTP rewrite module requires the PCRE library.
You can either disable the module by using --without-http_rewrite_module
option, or install the PCRE library into the system, or build the PCRE library
statically from the source with nginx by using --with-pcre=<path> option.
```
使用yum安装pcre  
```sh
yum install pcre-devel
```

### 4.安装zlib  
查看zlib zlib-devel版本，若不存在则需要安装  
```sh
rpm -qa zlib zlib-devel
```
使用yum安装
```sh
yum install zlib
yum install zlib-devel
```

### 5.（可选）安装openssl   
查看openssl openssl-devel版本，若不存在则需要安装  
```sh
openssl version
rpm -qa openssl openssl-devel
```
使用yum安装
```sh
yum install openssl
yum install openssl-devel
```

## 下载安装包
### 1.下载nginx源码
(1)进入nginx下载页，获取源码包链接  
https://nginx.org/en/download.html  
![nginx download](../.pic/nginx%20download.png)  
(2)使用wget下载文件
```sh
wget https://nginx.org/download/nginx-1.25.4.tar.gz
```
(3)解压源码包  
```sh
tar -zxvf nginx-1.25.4.tar.gz
```

### 2.(可选)下载nginx扩展模块
#### 2.1下载echo-nginx-module
https://github.com/openresty/echo-nginx-module  
使用wget下载文件  
```sh
wget https://github.com/openresty/echo-nginx-module/archive/refs/tags/v0.63.tar.gz
```
(3)解压源码包  
```sh
tar -zxvf v0.63.tar.gz
```

## 编译安装
### 1.使用configure创建MakeFile文件  
```
./configure --prefix=/opt/nginx --with-http_ssl_module --add-module=/home/echo-nginx-module-0.63
```
### 2.编译
```sh
make
```
### 3.安装
```sh
make install
```

