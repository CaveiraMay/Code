#include "ThreadPool.h"
#include "Tool.h"
#include <iostream>
#include <chrono>
#include <thread>

using uLong = unsigned long long;
class MyTask: public Task 
{
public:
        MyTask(int begin, int end)
        : begin_(begin)
        , end_(end)
        {}
        Any run() {
                try {
                        std::cout << "MyTask run, tid: " << std::this_thread::get_id() << std::endl;
                        // std::this_thread::sleep_for(std::chrono::seconds(5));
                        uLong sum = 0;
                        for(int i = begin_; i < end_; ++i) {
                                sum += i;
                        }
                        std::cout << "MyTask run finished, tid: " << std::this_thread::get_id()  << "sum: " << sum << std::endl;
                        return sum;
                }catch(const std::exception e) {
                        std::cout << "MyTask run failed, exception: " << e.what() << std::endl;
                }
                return {};
        }
private:
        int begin_;
        int end_;
};

int main() {
        ThreadPool pool;
        pool.start();

        Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 1000));
        Result res2 = pool.submitTask(std::make_shared<MyTask>(1001, 2000));
        Result res3 = pool.submitTask(std::make_shared<MyTask>(2001, 3000));

        uLong sum1 = res1.get().cast_<uLong>();
        uLong sum2 = res2.get().cast_<uLong>();
        uLong sum3 = res3.get().cast_<uLong>();

        std::cout << "total: " << sum1 + sum2 + sum3 << std::endl;

        // std::this_thread::sleep_for(std::chrono::seconds(5));
        getchar();
        return 0;
}