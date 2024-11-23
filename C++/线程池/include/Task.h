#ifndef TASK_H
#define TASK_H

#include "Tool.h"

//任务抽象基类
class Task
{
public:
    Task();
    ~Task() = default;
    virtual Any run() = 0;     //用户可以自定义任意任务类型, 从 Task 继承，重写 run()方法, 实现自定义任务处理
    void exec();
    void setResult(Result* res);
private:
    //裸指针, 避免智能指针交叉定义无法释放
    Result* result_;    //生命周期(同 task)
};

#endif