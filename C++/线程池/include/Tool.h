#ifndef TOOL_H
#define TOOL_H

#include <iostream>
#include <memory>

//Any 类型: 可以接受任何类型的数据
class Any
{
public:
        Any() = default;
        ~Any() = default;
        Any(const Any&) = delete;
        Any& operator=(const Any&) = delete;
        Any(Any&&) = default;
        Any& operator=(Any&&) = delete;
        
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
                private:
                        T data_;
        };

        //定义一个基类指针
        std::unique_ptr<Base> base_;
};

#endif