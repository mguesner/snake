#include "Multi.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <csignal>

typedef struct protoent		t_protoent;
typedef struct sockaddr		t_sockaddr;
typedef struct hostent		t_hostent;
typedef struct in_addr		t_in_addr;

Multi::Multi()
{
	isConnect = false;
	isListening = false;
	signal(SIGPIPE, SIG_IGN);

}

Multi::Multi(Multi const & src)
{
	(void)src;
}

void Multi::Host()
{
	if (!isConnect && !isListening)
	{
		t_protoent		*prot;
		if (!(prot = getprotobyname("tcp")))
			perror("getprotobyname");
		if ((sock = socket(PF_INET, SOCK_STREAM, prot->p_proto)) == -1)
		{
			perror("socket");
			return;
		}
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(PORT);
		if (bind(sock, (t_sockaddr*)&sin, sizeof(sin)) == -1)
		{
			perror("bind");
			return;
		}
		if (listen(sock, 1) == -1)
		{
			perror("listen");
			return;
		}
		isListening = true;
	}
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
		return;
	}
	if(FD_ISSET(sock, &readfs))
	{
		unsigned int sinsize = sizeof sin;
		cSock = accept(sock, (t_sockaddr *)&sin, &sinsize);
		isConnect = true;
		isListening = false;
	}
}

void Multi::Join(std::string ip)
{
	t_sockaddr_in	sin;
	t_protoent	*proto;
	if ((proto = getprotobyname("tcp")) == NULL)
		perror("prot");
	if ((cSock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		perror("sock");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr = *(t_in_addr *)(gethostbyname(ip.c_str())->h_addr);
	std::cout << "CONNECTION..." << std::endl;
	if (connect(cSock, (t_sockaddr *)&sin, sizeof(sin)) == -1)
		perror("connect");
	else
		isConnect = true;
	std::cout << "DONE..." << std::endl;
}

void Multi::Send(void *data, int size)
{
	char res[2];
	write(cSock, data, size);
	read(cSock, res, 1);
}

bool Multi::Rcv(char data[128])
{
	if (!isConnect)
		return false;
	if (read(cSock, data, 127) == -1)
	{
		std::cout << "Multi.cpp error PIPE read" << std::endl;
		exit(-1);
	}
	write(cSock, "1", 1);
	// std::cout << "rcv : " << data << std::endl;
	return true;
}

Serializer Multi::Rcv()
{
	Serializer data;
	if (!isConnect)
		return data;
	if (read(cSock, &data, sizeof(Serializer)) == -1)
	{
		std::cout << "Multi.cpp error PIPE read" << std::endl;
		exit(-1);
	}
	write(cSock, "1", 1);
	// std::cout << "rcv : " << data << std::endl;
	return data;
}

bool Multi::IsConnect()
{
	return isConnect;
}

void Multi::Disconnect()
{
	isConnect = false;
	close(cSock);
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

