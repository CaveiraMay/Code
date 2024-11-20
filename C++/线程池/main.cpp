#include "ThreadPool.h"
#include <iostream>
#include <chrono>
#include <thread>

class MyTask: public Task 
{
public:
        void run() {
                std::cout << "MyTask run, tid: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(5));
                std::cout << "MyTask run finished, tid: " << std::this_thread::get_id() << std::endl;
        }
};

int main() {
        ThreadPool pool;
        pool.start();
        pool.submitTask(std::make_shared<MyTask>());
        pool.submitTask(std::make_shared<MyTask>());
        pool.submitTask(std::make_shared<MyTask>());
        pool.submitTask(std::make_shared<MyTask>());
        pool.submitTask(std::make_shared<MyTask>());
        pool.submitTask(std::make_shared<MyTask>());
        pool.submitTask(std::make_shared<MyTask>());
        pool.submitTask(std::make_shared<MyTask>());
        pool.submitTask(std::make_shared<MyTask>());
        pool.submitTask(std::make_shared<MyTask>());

        // std::this_thread::sleep_for(std::chrono::seconds(5));
        getchar();
        return 0;
}