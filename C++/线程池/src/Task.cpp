#include "Task.h"

Task::Task()
: result_(nullptr)
{}

void Task::exec()
{
        if(result_ != nullptr) {
                //这里执行多态方法
                result_->setVal(run());
        }
}

void Task::setResult(Result* res)
{
    result_ = res;
}