#include "ThreadPool.h"
#include "Tool.h"
#include <functional>
#include <iostream>
#include <thread>

const int TASK_MAX_THRESHHOLD = 4;

ThreadPool::ThreadPool()
        :initThreadSize_(4)
        ,taskSize_(0)
        ,taskQueThreshHold_(TASK_MAX_THRESHHOLD)
        ,poolMode_(ThreadPoolMode::MODE_FIXED)
{

}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::setMode(ThreadPoolMode mode)
{
    poolMode_ = mode;
}

void ThreadPool::setTaskQueMaxThreshHold(int threshHold)
{
    taskQueThreshHold_ = threshHold;
}

Result ThreadPool::submitTask(std::shared_ptr<Task> task)
{
        //获取锁
        std::unique_lock<std::mutex> lock(TaskQueMtx_);
        //线程的通信, 等待任务队列有空余
        /* while(taskQue_.size() == taskQueThreshHold_) {
        //         notFull_.wait(lock);
         }*/
        //用户提交任务, 最长不能阻塞超过 1s, 否则判断提交任务失败, 返回
        if(!notFull_.wait_for(lock, std::chrono::seconds(1),
                [&]()-> bool {return taskQue_.size() < (size_t)taskQueThreshHold_;})) {
                        //表示notFull_等待 1s 条件依然没有得到满足
                        std::cerr << "task queue is Full, submit task fail!" << std::endl;
                        return Result(task, false);
                }
        //如果有空余, 把任务放在任务队列中
        taskQue_.emplace(task);
        taskSize_++;
        //因为新放了任务, 任务队列肯定不为空, 使用 notEmpty_ 通知, 赶快分配线程执行任务

        notEmpty_.notify_all();
        //返回任务的 Result 对象
        return Result(task);
}

void ThreadPool::start(int initThreadSize)
{
        //记录初始线程数量
        initThreadSize_ = initThreadSize;
        //创建线程对象
        for(int i = 0; i < initThreadSize_; i++) {
                std::unique_ptr<Thread> ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this));
                threads_.emplace_back(std::move(ptr));
        }
        //启动所有线程
        for(int i = 0; i < initThreadSize_; i++) {
                threads_[i]->start();
        }
}

void ThreadPool::threadFunc()
{
        // std::cout << "begin threadFunc, tid is:" << std::this_thread::get_id() << std::endl;
        // std::cout << "end threadFunc, tid is:" << std::this_thread::get_id() << std::endl;
        for(;;) {
                std::shared_ptr<Task> task;
                {
                        //先获取锁
                        std::unique_lock<std::mutex> lock(TaskQueMtx_);
                        std::cout << "尝试获取任务, tid: " << std::this_thread::get_id() << std::endl;
                        //等待notEmpty_条件
                        notEmpty_.wait(lock, [&]()-> bool {return taskQue_.size() > 0;});
                        std::cout << "获取任务成功, tid: " << std::this_thread::get_id() << std::endl;
                        //从任务队列中取一个任务出来
                        task = taskQue_.front();
                        taskQue_.pop();
                        taskSize_--;
                        //如果依然有剩余任务, 继续通知其他线程执行任务
                        if(taskQue_.size() > 0) {
                                notEmpty_.notify_all();
                        }
                        //取出一个任务, 进行通知, 可以继续提交生产任务
                        notFull_.notify_all();
                }//释放锁, 让其他线程操作任务队列取任务
                if(task != nullptr) {
                        //当前线程负责执行这个任务, 执行完成后调用 Result.setVal()
                        // task->run();
                        task->exec();
                }
        }
}