#ifndef TASK_H
#define TASK_H

//任务抽象基类
class Task
{
public:
    virtual void run() = 0;     //用户可以自定义任意任务类型, 从 Task 继承，重写 run()方法, 实现自定义任务处理
};

#endif