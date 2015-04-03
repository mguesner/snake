#ifndef MULTI_HPP
#define MULTI_HPP

#define PORT	6666

class Multi
{
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
	bool isConnect;
	int  cSock;
};

#endif
