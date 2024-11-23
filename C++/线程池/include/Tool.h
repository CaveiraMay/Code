#ifndef TOOL_H
#define TOOL_H

// #include "Task.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <atomic>
#include <condition_variable>

class Task;

//Any 类型: 可以接受任何类型的数据
class Any
{
public:
        Any() = default;
        ~Any() = default;
        Any(const Any&) = delete;
        Any& operator=(const Any&) = delete;
        Any(Any&&) = default;
        Any& operator=(Any&&) = default;
        
        template<typename T>
        Any(T data): base_(std::make_unique<Derived<T>>(data))
        {}
        //把 Any 对象中存储的 data 数据拿出来
        template<typename T>
        T cast_() {
                //从 base_中找到它所指向的 Derived 对象, 并取出其 data 成员变量的值
                //基类指针 => 派生类指针        RTTI
                Derived<T> *pd = dynamic_cast<Derived<T>*>(base_.get());
                if(pd == nullptr) {
                        throw "type is unmatched!";
                }
                return pd->data_;
        }
private:
        //基类类型
        class Base
        {
                public:
                        virtual ~Base() = default;
        };

        //派生类类型
        template<typename T>
        class Derived : public Base
        {
                public:
                        Derived(T data): data_(data)
                        {} 
                // private:
                        T data_;
        };

        //定义一个基类指针
        std::unique_ptr<Base> base_;
};


//实现一个信号量类
class Semaphore
{
public:
        Semaphore(int limit = 0)
        : resLimit_(1)
        {}
        ~Semaphore() = default;

        //获取一个信号量资源
        void wait() {
                std::unique_lock<std::mutex> lock(mtx_);
                //等待信号量有资源, 没有资源的话会阻塞当前线程
                cond_.wait(lock, [&]()-> bool {return resLimit_ > 0;});
                resLimit_--;
        }
        //增加一个信号量资源
        void post() {
                std::unique_lock<std::mutex> lock(mtx_);
                resLimit_++;
                cond_.notify_all();
        }
private:
        int resLimit_;
        std::mutex mtx_;
        std::condition_variable cond_;
};

//实现接收提交到线程池的 task 任务执行完成后的返回值类型
class Result
{
public:
        Result(std::shared_ptr<Task> task, bool isValid = true);
        ~Result() = default;

        //给 task 设置返回值
        void setVal(Any any);

        //用户获取 task 返回值
        Any get();
private:
        Any any_;       //存储任务的返回值
        Semaphore sem_; //线程通信信号量
        std::shared_ptr<Task> task_;    //指向对应获取返回值的任务对象 
        std::atomic_bool isValid_;      //返回值是否有效
};
#endif