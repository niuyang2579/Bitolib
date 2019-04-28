#ifdef LOOPERTHREAD_H
#define LOOPERTHREAD_H

#include <thread>
#include <mutex>
#include <condition_variable>

class Looper;

class LooperThread
{
public:
	LooperThread();
	~LooperThread();

	Looper* GetLoop();
	
};

#endif // LOOPERTHREAD_H