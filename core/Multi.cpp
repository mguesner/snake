#include "Multi.hpp"
#include "unistd.h"
#include <netdb.h>
#include <stdio.h>
#include <sys/time.h>
#include <iostream>
#include <sys/socket.h>

typedef struct protoent		t_protoent;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;
typedef struct hostent		t_hostent;
typedef struct in_addr		t_in_addr;

Multi::Multi()
{
}

Multi::Multi(Multi const & src)
{
	(void)src;
}

void Multi::Host()
{
	t_protoent		*prot;
	t_sockaddr_in	sin;
	int				sock;

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
	unsigned int sinsize = sizeof sin;
	if ((cSock = accept(sock, (t_sockaddr *)&sin, &sinsize)) == -1)
		perror("accept");
		std::cout << "accepted" << std::endl;
		isConnect = true;
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
		std::cout << "fail" << std::endl;
		perror("conn");
		exit(-1);
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
}

