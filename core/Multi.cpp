#include "Multi.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

typedef struct protoent		t_protoent;
typedef struct sockaddr		t_sockaddr;
typedef struct hostent		t_hostent;
typedef struct in_addr		t_in_addr;

Multi::Multi()
{
	t_protoent		*prot;
	isConnect = false;
	if (!(prot = getprotobyname("tcp")))
		perror("getprotobyname");
	if ((sock = socket(PF_INET, SOCK_STREAM, prot->p_proto)) == -1)
		perror("socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(PORT);
	if (bind(sock, (t_sockaddr*)&sin, sizeof(sin)) == -1)
		perror("bind");
	if (listen(sock, 1) == -1)
		perror("listen");
}

Multi::Multi(Multi const & src)
{
	(void)src;
}

void Multi::Host()
{
	fd_set readfs;
	int ret = 0;
	FD_ZERO(&readfs);
	FD_SET(sock, &readfs);
	struct timeval	timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	if((ret = select(sock + 1, &readfs, NULL, NULL, &timeout)) < 0)
	{
		perror("select");
		exit(errno);
	}
	if(FD_ISSET(sock, &readfs))
	{
		unsigned int sinsize = sizeof sin;
		cSock = accept(sock, (t_sockaddr *)&sin, &sinsize);
		isConnect = true;
	}
}

void Multi::Join()
{
	t_sockaddr_in	sin;
	t_protoent	*proto;
	if ((proto = getprotobyname("tcp")) == NULL)
		perror("prot");
	if ((cSock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		perror("sock");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(6666);
	sin.sin_addr = *(t_in_addr *)(gethostbyname("localhost")->h_addr);
	if (connect(cSock, (t_sockaddr *)&sin, sizeof(sin)) == -1)
	{
		perror("conn");
		exit(errno);
	}
	isConnect = true;
}

void Multi::Send(void *data, int size)
{
	write(cSock, data, size);
}

void Multi::Rcv(char data[128])
{
	read(cSock, data, 127);
}

bool Multi::IsConnect()
{
	return isConnect;
}

Multi& Multi::operator=(Multi const & rhs)
{
	(void)rhs;
	return *this;
}

Multi::~Multi()
{
	close(sock);
	close(cSock);
}

