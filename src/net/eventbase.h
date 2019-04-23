#ifndef EVENTBASE_H
#define EVENTBASE_H

#include "timestamp.h"
#include <sys/epoll.h>
#include <functional>

// 事件基类，内含epoll_event的内容及相应事件处理函数
class EventBase
{
public:
	using Callback = std::function<void()>;
	using ReadCallback = std::function<void(Timestamp)>;

	// 传入参数为文件描述符
	EventBase(int fd);
	~EventBase();

	// 关注可读事件
	void EnableReadEvents() { events_ |= (EPOLLIN | EPOLLPRI); }
	// 关注可写事件
	void EnableWriteEvents() { events_ |= EPOLLOUT; }
	// 取消关注相应事件
	void DisableReadEvents() { events_ &= ~(EPOLLIN | EPOLLPRI); }
	void DisableWriteEvents()  { events_ &= ~EPOLLOUT; }

	// 设置相应的事件处理函数
	void SetReadCallback(ReadCallback&& cb)  {read_callback_ = cb;}
	void SetWriteCallback(Callback&& cb) { write_callback_ = cb; }
    void SetErrorCallback(Callback&& cb) { error_callback_ = cb; }
    void SetCloseCallback(Callback&& cb) { close_callback_ = cb; }

	// 分发事件
	void HandleEvent();
private:
	// 文件描述符
	const int fd_;
	// 关注的事件
	int events_;

	// 返回的活跃事件
	int revents_;

	// 事件处理函数
	ReadCallback read_callback_;
	Callback write_callback_;
	Callback error_callback_;
	Callback close_callback_;
};

#endif // EVENTBASE_H