#include "connection.h"
#include "eventbase.h"
#include "looper.h"
#include "logger.h"
#include "util.h"
#include <unistd.h>

Connection::Connection(Looper* loop, int conn_sockfd, const struct sockaddr_in& local_addr, const struct sockaddr_in peer_addr):
	loop_(loop),
	conn_sockfd_(conn_sockfd),
	conn_eventbase_(new Eventbase(conn_sockfd_)),
	local_addr_(local_addr),
	peer_addr_(peer_addr),
	context_(nullptr)
{
	conn_eventbase_->SetReadCallback(std::bind(&Connection::HandleRead, this, std::placeholder::_1));
	conn_eventbase_->SetWriteCallback(std::bind(&Connection::HandleWrite, this));
	conn_eventbase_->SetCloseCallback(std::bind(&COnnection::HandleClose, this));
	conn_eventbase_->EnableReadEvents();
}

Connection::~Connection()
{
	util::Close(conn_sockfd_);
}

// 连接建立后在分配的线程上注册事件
void Connection::Register()
{
	loop_->AddEventBase(conn_eventbase_);
	if (connection_established_cb_)
		connection_established_cb_(shared_from_this());
}