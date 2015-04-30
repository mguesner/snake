#ifndef MULTI_HPP
#define MULTI_HPP

#define PORT	6666

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/time.h>
#include <string>
#include "Serializer.hpp"

class Multi
{
typedef struct sockaddr_in	t_sockaddr_in;
public:
	Multi();
	void Host();
	void Join(std::string ip);
	void Send(void *data, int size);
	bool Rcv(char data[128]);
	Serializer Rcv();
	Multi(Multi const & src);
	void Disconnect();
	bool IsConnect();
	Multi& operator=(Multi const & rhs);
	~Multi();

private:
	bool	isConnect;
	bool	isListening;
	int		sock;
	int		cSock;
	t_sockaddr_in	sin;
};

#endif
