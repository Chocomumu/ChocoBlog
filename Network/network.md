## 01 ����

������ͨ����д����ʵ�ֲ�ͬ�����������Ͻ�������  

����ϵͳ�ṩ�׽��֣�socket�����������һ̨��������������豸  

���ǽ��������̣����ǻ���socket���г����д  

�������ֳ�Ϊsocket���  

P.S. socket �����������ӵ�����Ľӿڵĺ���  

## 02���׽��ֱ������
### Linux���׽���
#### ���շ�

```C
#include <sys/socket.h>

/* 1.����socket���� */

int socket(int domain, int type, int protocol);

/* 2.����IP�Ͷ˿� */

int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);

/* 3.���ü���״̬ */

int listen(int sockfd, int backlog);

/* 4.���ܶԷ����� */

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

#### ����
```C
#include <sys/socket.h>

/* 1.����socket���� */

int socket(int domain, int type, int protocol);

/* 2.�������� */

int connect(int sockfd, struct sockaddr *addr, socklen_t addrlen);
```

### windows���׽���
#### ���շ�

```C
#include <winsock2.h>

/* ��ʼ��Winsock�� */

int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);

/* 1.����socket */

SOCKET socket(int af, int type, int protocol);

/* 2.����ip�Ͷ˿� */

int bind(SOCKET s, const struct sockaddr * name, int namelen);

/* 3.���ü���״̬ */

int listen(SOCKET s, int backlog);

/* 4.���ܶԷ����� */

SOCKET accept(SOCKET s, struct sockaddr *name, int *namelen);

/* 5.�ر�socket */

int closesocket(SOCKET s);

/* ע��Winsock�� */

int WSACleanup(void);
```

#### ����
```C
#include <winsock2.h>

/* ��ʼ��Winsock�� */

int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);

/* 1.����socket */

SOCKET socket(int af, int type, int protocol);


/* 2.���ܶԷ����� */

int connect(SOCKET s, struct sockaddr *name, int namelen);

/* 3.�ر�socket */

int closesocket(SOCKET s);

/* ע��Winsock�� */

int WSACleanup(void);
```


#### windows��ʹ��gcc���б����ָ��
```
gcc  -lwsock32
```

### linux��Windows���׽�����غ����ıȽ�
1.Windows����Ҫʹ��WSAStarup��WSAClean����  
2.linux����ʹ��write��read�����ļ���д�ĺ������ͽ�������

### socket()����

```C
// linux��ԭ��
int socket(int domain, int type, int protocol);
// Windows��ԭ��
SOCKET socket(int af, int type, int protocol);
```
#### ����ֵ
���߷���ֵ���Ǵ�����socket������Linux��Ϊint�ͣ�Ϊ�ļ�fd��Windows��ΪSOCKET���ͣ������͵Ķ��壩��  


#### ��������

1.protocol family Э����  

PF_INET  
PF_INET6  
PF_LOCAL  
PF_PACKET  
PF_IPX  

2.socket type �׽�������  
�����׽��ֵĴ��䷽ʽ  

(1)�������ӵ��׽��� SOCK_STREAM
(2)�������ӵ��׽��� SOCK_DGRAM

3.protocol Э��

PF_INET SOCK_STREAM �µ�Э��ֻ��һ�֣�IPPROTO_TCP


