#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "Thread.h"
#include "Task.h"

//线程池支持的模式
enum class ThreadPoolMode
{
    MODE_FIXED, //固定数量的线程池
    MODE_CACHED //线程数量可动态增长的线程池
};

/*
example:
ThreadPool pool;
pool.start(4);

class MyTask: public Task
{
public:
        void run() {//线程代码...}
};

pool.submitTask(std::make_shared<MyTask>()););
*/
//线程池类型
class ThreadPool
{
public:
        //线程池构造
        ThreadPool();
        //线程池析构
        ~ThreadPool();
        //设置线程池的工作模式
        void setMode(ThreadPoolMode mode);
        //设置任务队列上限阈值
        void setTaskQueMaxThreshHold(int threshHold);
        //给线程池提交任务
        Result submitTask(std::shared_ptr<Task> task);
        //开启线程池
        void start(int initThreadSize = 4);
        //禁止拷贝
        ThreadPool(const ThreadPool&) = delete;
        //禁止复制
        ThreadPool& operator=(const ThreadPool&) = delete;
private:
        //提供线程函数
        void threadFunc();
private:
        std::vector<std::unique_ptr<Thread>> threads_;  //线程列表
        size_t initThreadSize_;         //初始的线程数量
        std::queue<std::shared_ptr<Task>> taskQue_;   //任务队列
        std::atomic_int taskSize_;      //任务的数量
        int taskQueThreshHold_;       //任务队列上线阈值
        std::mutex TaskQueMtx_;       //保证任务队列的线程安全
        std::condition_variable notFull_;       //表示任务队列不满
        std::condition_variable notEmpty_;      //表示任务队列不空
        ThreadPoolMode poolMode_;       //线程池类型
};

#endif