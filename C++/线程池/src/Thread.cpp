#include "Thread.h"
#include <thread>

Thread::Thread(ThreadFunc func)
        :func_(func)
{
        
}

Thread::~Thread()
{
        
}

void Thread::start()
{
        //创建一个线程来执行一个线程函数
        std::thread t(func_);
        //设置分离线程
        t.detach();
}