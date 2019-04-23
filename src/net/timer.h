#ifndef TIME_H
#define TIME_H

#include "timestamp.h"
#include <stdint.h>
#include <functional>

class Timer
{
public:
	 Timer(const std::function<void()>&cb, Timestamp when):
	 	callback_(cb),
	 	when_(when) {}

	 void Run() const { callback_(); }
	 Timestamp GetExpTime() const { return when_; }

private:
	const std::function<void()> callback_;
	Timestamp when_;
};

#endif  // TIME_H