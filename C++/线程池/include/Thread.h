#ifndef THREAD_H
#define THREAD_H

#include <functional>

//线程类型
class Thread
{
public:
        //线程函数对象类型
        using ThreadFunc = std::function<void()>;
        //线程构造函数
        Thread(ThreadFunc func);
        //线程析构函数
        ~Thread();
        //启动线程
        void start();
private:
        ThreadFunc func_;
};

#endif