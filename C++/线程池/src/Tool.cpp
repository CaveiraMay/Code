#include "Tool.h"
#include "Task.h"

Result::Result(std::shared_ptr<Task> task, bool isValid)
: isValid_(isValid)
, task_(task)
{
        task->setResult(this);
}

void Result::setVal(Any any)
{
        std::cout << "Result::setVal" << std::endl;
        //存储 task 的返回值
        this->any_ = std::move(any);
        //已经获取任务的返回值, 增加资源信号量
        sem_.post();
}

Any Result::get() 
{
        if(isValid_) {
                return "";
        }
        sem_.wait();    //task 如果没有执行完, 这里会阻塞用户的线程
        return std::move(any_);
}