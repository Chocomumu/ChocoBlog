# nginx配置-location
```
Syntax:	    location [ = | ~ | ~* | ^~ ] uri { ... }
            location @name { ... }
Default:    —
Context:    server, location
```

### location配置可以有两种标记方法：  
1.修饰符 + uri  
这种方式根据请求的uri进行匹配；  
2.@name  
这种方式可以定义一个用于内部使用的location配置；  
可用于重定向。  

### location块可以配置在server块和location块中  
location块在部分场景下支持嵌套，并非所有的location块都可以嵌套配置。  

# location的URI匹配  
nginx的配置中，location块的选择根据请求的uri选择配置。  
匹配是基于规范的uri进行的，规范化进行以下三个操作：  
a.解码“%XX”类型的格式；  
b.处理带有“.”、“..”的相对路径；  
c.将多个“/”压缩为单个“/”（可通过配置merge_slashes开关）。  

## 匹配方法的分类
uri的匹配方式可以分为精准匹配、前缀匹配、带修饰符的前缀匹配、大小写不敏感的正则匹配、大小写不敏感的正则匹配。  

### 精准匹配
精准匹配在请求uri和配置的uri完全相同时，会命中该location配置。   
精准匹配通过修饰符“=”标记，语法如下。  
```nginx
location = uri {
    [configuration]
}
```
精准匹配的优先级最高。 

##### 相关实验
[精准匹配](#实验一精准匹配)  

### 前缀匹配
location的uri前缀匹配是进行字符串的前缀匹配，若请求的uri以配置的字符串开头（大小写敏感），则命中配置。  
前缀匹配可以分为两类：无修饰符的前缀匹配和带修饰符的前缀匹配。  

#### 无修饰符的前缀匹配
当配置location时不带修饰符，则进行前缀匹配。  
```nginx
location uri {
    [configuration]
}
```

##### 相关实验
[无修饰符前缀匹配](#实验二无修饰符前缀匹配)  

#### 根路径匹配
特别关注特殊的"/"前缀配置，有时候会配置一个兜底的根路径匹配。  
如果本身根路径的访问就是一个频繁场景，可以配置对于"/"的精准匹配加快命中速度。  
```nginx
# 兜底的匹配
location / {
    [configuration]
}
# 根路径的精准匹配
location =/ {
    [configuration]
}
```

##### 相关实验
["/"的精准匹配](#实验四slash的精准匹配)  

注：特别的，对于根路径匹配，无路请求的域名或IP后是否带"/"，都会命中"/"的精准匹配。  

#### 带修饰符的前缀匹配
前缀匹配可以通过修饰符"^~"显式表示，语法如下。  
```nginx
location ^~ uri {
    [configuration]
}
```

##### 相关实验
[带修饰符前缀匹配](#实验三带修饰符前缀匹配)  

#### 优先级
(1)是否有修饰符的前缀匹配的优先级是不一样的；  
a.不带修饰符  
不带修饰符的location的命中优先级最低，虽然nginx会优先查找前缀匹配，但是如果命中的是无修饰符的location配置，命中后还会去寻找是否有匹配的正则匹配。  
b.带修饰符
带修饰符的location的命中优先级排在所有类型中第二位，仅次于精准匹配，若命中的最长前缀带修饰符，则查找结束，使用该规则。 

(2)前缀匹配内部的优先级规则是：选择更长的匹配前缀，即当配置中多个前缀命中，会选择最长的前缀配置。无论是否带修饰符，都被放到一起进行匹配，选择所有前缀中最长前缀。  

### 正则匹配
正则匹配是根据请求的uri进行验证。  
正则匹配分为两种：大小写不敏感的正则匹配、大小写不敏感的正则匹配。  
大小写敏感的正则匹配语法如下：  
```nginx
location ~ uri {
    [configuration]
}
```
大小写不敏感的正则匹配语法如下：  
```nginx
location ~* uri {
    [configuration]
}
```

##### 相关实验
[正则匹配](#正则匹配)  

#### 优先级
(1)正则的优先级低于带修饰符的前缀匹配，高于不带修饰符的前缀匹配；  
(2)正则匹配内部的优先级规则是：选择第一个命中的正则匹配。  

## location的优先级
1.命中精准匹配（=）  
2.命中带修饰符的前缀匹配（^~）  
3.命中正则匹配（~/~*）  
4.命中不带修饰符的前缀匹配  

## 附录A、实验
#### 注意：实验中使用了nginx的echo-nginx-module模块
### 实验一：精准匹配
a.在server下配置如下的location，  
```nginx
location = /precise {
    echo "match equal /precise location";
}
```

b.使用curl命令访问：“ip\[:port\]或domain name+/precise”。  
成功访问，控制台会打印数据：  
```sh
match equal /precise location
```

c.使用curl命令访问：“ip\[:port\]或domain name+/precise/”（多了一个“/”）。  
访问应答404。  
```sh
<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.25.4</center>
</body>
</html>
```

### 实验二：无修饰符前缀匹配
a.在server下配置如下的location，  
```nginx
location /pure_prefix {
    echo "match /pure_prefix location";
}
```

b.使用curl命令访问以下链接：  
"ip\[:port\]或domain name+/pure_prefix"  
"ip\[:port\]或domain name+/pure_prefix/"  
"ip\[:port\]或domain name+/pure_prefix/123"  
"ip\[:port\]或domain name+/pure_prefix1"  
"ip\[:port\]或domain name+/pure_prefix1/123"  
成功访问，控制台会打印数据：  
```sh
match /pure_prefix location
```

c.使用curl命令访问：“ip\[:port\]或domain name+/Pure_Prefix/”（大写了"p"）。  
访问应答404。  
```sh
<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.25.4</center>
</body>
</html>
```

### 实验三：带修饰符前缀匹配
a.在server下配置如下的location，  
```nginx
location ^~ /prefix {
    echo "match /prefix with modifier location";
}
```

b.使用curl命令访问以下链接：  
"ip\[:port\]或domain name+/prefix"  
"ip\[:port\]或domain name+/prefix/"  
"ip\[:port\]或domain name+/prefix/123"  
"ip\[:port\]或domain name+/prefix"  
"ip\[:port\]或domain name+/prefix/123"  
成功访问，控制台会打印数据：  
```sh
match /prefix with modifier location
```

c.使用curl命令访问：“ip\[:port\]或domain name+/Prefix/”（大写了"p"）。  
访问应答404。  
```sh
<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.25.4</center>
</body>
</html>
```

### 实验四：slash的精准匹配
a.在server下配置如下的location，  
```nginx
location =/ {
    echo "match equal slash location";
}
```

b.使用curl命令访问以下链接：  
"ip\[:port\]或domain name"  
"ip\[:port\]或domain name+/"  
成功访问，控制台会打印数据：  
```sh
match equal slash location
```

### 实验五：正则匹配
a.在server下配置如下的location，  
```nginx
# 大小写敏感的正则匹配
location ~ /reg* {
    echo "match /reg* case-sensitive location";
}
# 大小写不敏感的正则匹配
location ~* /reg* {
    echo "match /reg* case-insensitive location";
}
```

b.使用curl命令访问以下链接：  
"ip\[:port\]或domain name/Reg1"  
成功访问，匹配到大小写敏感的配置，控制台会打印数据：  
```sh
match /reg* case-insensitive location
```
"ip\[:port\]或domain name/reg1"   
成功访问，匹配到大小写敏感的配置，控制台会打印数据：  
```sh
match /reg* case-sensitive location
```
#### 注：若配置中的顺序颠倒，则都会匹配到大小写不敏感的配置，这是由于正则会在找到第一个符合条件的配置结束。  
