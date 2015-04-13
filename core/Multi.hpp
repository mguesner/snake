#ifndef MULTI_HPP
#define MULTI_HPP

#define PORT	6666

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/time.h>

class Multi
{
typedef struct sockaddr_in	t_sockaddr_in;
public:
	Multi();
	void Host();
	void Join();
	void Send(void *data, int size);
	void Rcv(char data[128]);
	Multi(Multi const & src);
	bool IsConnect();
	Multi& operator=(Multi const & rhs);
	~Multi();

private:
	bool	isConnect;
	int		sock;
	int		cSock;
	t_sockaddr_in	sin;
};

#endif
