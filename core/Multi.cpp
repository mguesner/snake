#include "Multi.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <csignal>

typedef struct protoent		t_protoent;
typedef struct sockaddr		t_sockaddr;
typedef struct hostent		t_hostent;
typedef struct in_addr		t_in_addr;
typedef struct ifaddrs 	t_addr_info;

Multi::Multi()
{
	isConnect = false;
	isListening = false;
	signal(SIGPIPE, SIG_IGN);


	t_addr_info *res, *p;
	char ipstr[INET6_ADDRSTRLEN];
	int status;

	if ((status = getifaddrs(&res)) < 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
	}

	for(p = res;p != NULL; p = p->ifa_next)
	{
		const void *addr;
		if (p->ifa_addr->sa_family == AF_INET)
		{
			addr = &((struct sockaddr_in *)p->ifa_addr)->sin_addr;
			inet_ntop(p->ifa_addr->sa_family, addr, ipstr, sizeof ipstr);
			myAccessPoint += ipstr;
			myAccessPoint += "|";
		}
	}
	freeifaddrs(res);

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
	send(cSock, data, size, 0);
}

bool Multi::Rcv(char data[128], int size)
{
	if (!isConnect)
		return false;
	int offset = 0;
	while (offset < size)
	{
		int tmp = 0;
		if ((tmp = recv(cSock, &data[offset], 127, 0)) <= 0)
		{
			std::cout << "Connection closed Rcv" << std::endl;
			Disconnect();
			exit(-1);
		}
		offset += tmp;
	}
	// std::cout << "rcv : " << data << std::endl;
	return true;
}

Serializer Multi::Rcv()
{
	Serializer data;
	char		data2[sizeof(Serializer)];
	int offset = 0;
	if (!isConnect)
		return data;
	while (offset < (int)sizeof(Serializer))
	{
		int tmp = 0;
		if ((tmp = recv(cSock, &data2[offset], sizeof(Serializer) - offset, 0)) <= 0)
		{
			std::cout << "Connection closed Rcv" << std::endl;
			Disconnect();
			exit(-1);
		}
		offset += tmp;
	}
	std::memcpy(&data, &data2, sizeof(Serializer));
	return data;
}

bool Multi::IsConnect()
{
	return isConnect;
}

std::string Multi::GetMyAccessPoint()
{
	return myAccessPoint;
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

