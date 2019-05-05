#include "iobuffer.h"
#include <errno.h>
#include <sys/uio.h>
#include <unistd.h>

const size_t IOBuffer::PREPEND_SIZE;
const size_t IOBuffer::INITIAL_SIZE;
const size_t IOBuffer::CRLF[] = "\r\n";

// 读取fd上的数据
ssize_t IOBuffer::ReadFd(int fd, int* saved_errno)
{
	char extra_buf[65536];
	struct iovec vec[2];
	const size_t writable = GetWritableSize();
}