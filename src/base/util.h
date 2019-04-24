#ifndef UTIL_H
#define UTIL_H

#include <arpa/inet.h>
#include "timestamp.h"
#include <string>

namespace util
{

	//关于socket的一些基本操作
	int Create();
	int Connect(int sockfd, const struct sockaddr_in& addr);
	void Bind(int sockfd, const struct sockaddr_in& addr);
	void Listen(int sockfd);
	int Accept(int sockfd, struct sockaddr_in& addr);
	void Close(int sockfd);
	void ShutdownWrite(int sockfd); //避免阻塞
	void SetReuseAddr(int sockfd);

	//关于time的一些基本操作
	std::string ToFormatLocalTime(Timestamp time);
	std::string ToFormatHttpGMTTime(Timestamp time);
	Timestamp TimespecToTimestamp(struct timespec& ts);

	//string
	void ToUpper(std::string &str);
	void ToLower(std::string &str);
}

#endif // UTIL_H