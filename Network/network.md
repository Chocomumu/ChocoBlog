## 01 介绍

网络编程通过编写程序实现不同机器在网络上交换数据  

操作系统提供套接字（socket）组件，这是一台机器的网络软件设备  

我们进行网络编程，多是基于socket进行程序编写  

网络编程又称为socket编程  

P.S. socket 插座，是连接到网络的接口的含义  

## 02简单套接字编程流程
### Linux下套接字
#### 接收方

```C
#include <sys/socket.h>

/* 1.创建socket对象 */

int socket(int domain, int type, int protocol);

/* 2.分配IP和端口 */

int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);

/* 3.设置监听状态 */

int listen(int sockfd, int backlog);

/* 4.接受对方请求 */

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

#### 请求方
```C
#include <sys/socket.h>

/* 1.创建socket对象 */

int socket(int domain, int type, int protocol);

/* 2.请求连接 */

int connect(int sockfd, struct sockaddr *addr, socklen_t addrlen);
```

### windows下套接字
#### 接收方

```C
#include <winsock2.h>

/* 初始化Winsock库 */

int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);

/* 1.创建socket */

SOCKET socket(int af, int type, int protocol);

/* 2.分配ip和端口 */

int bind(SOCKET s, const struct sockaddr * name, int namelen);

/* 3.设置监听状态 */

int listen(SOCKET s, int backlog);

/* 4.接受对方请求 */

SOCKET accept(SOCKET s, struct sockaddr *name, int *namelen);

/* 5.关闭socket */

int closesocket(SOCKET s);

/* 注销Winsock库 */

int WSACleanup(void);
```

#### 请求方
```C
#include <winsock2.h>

/* 初始化Winsock库 */

int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);

/* 1.创建socket */

SOCKET socket(int af, int type, int protocol);


/* 2.接受对方请求 */

int connect(SOCKET s, struct sockaddr *name, int namelen);

/* 3.关闭socket */

int closesocket(SOCKET s);

/* 注销Winsock库 */

int WSACleanup(void);
```


#### windows下使用gcc进行编译的指令
```
gcc  -lwsock32
```

### linux和Windows下套接字相关函数的比较
1.Windows下需要使用WSAStarup和WSAClean函数  
2.linux可以使用write和read基于文件读写的函数发送接收数据

### socket()函数

```C
// linux下原型
int socket(int domain, int type, int protocol);
// Windows下原型
SOCKET socket(int af, int type, int protocol);
```
#### 返回值
两者返回值都是创建的socket，其中Linux下为int型，为文件fd；Windows下为SOCKET类型（是整型的定义）。  


#### 函数参数

1.protocol family 协议族  

PF_INET  
PF_INET6  
PF_LOCAL  
PF_PACKET  
PF_IPX  

2.socket type 套接字类型  
决定套接字的传输方式  

(1)面向连接的套接字 SOCK_STREAM
(2)面向连接的套接字 SOCK_DGRAM

3.protocol 协议

PF_INET SOCK_STREAM 下的协议只有一种，IPPROTO_TCP


