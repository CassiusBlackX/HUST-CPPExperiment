//
// Created by cassius on 2023/10/2.
//

#ifndef EX3_STACK_H
#define EX3_STACK_H
#include <string>
#include "Queue.h"

class Stack : public Queue {
private:
    Queue q;
public:
    explicit Stack(int m);                    		//初始化栈：最多存放2m-2个元素
    Stack(const Stack& s);         		//用栈s深拷贝初始化栈
    Stack(Stack&& s)noexcept;     		//用栈s移动拷贝初始化栈
    [[nodiscard]] int size() const noexcept override;		  		//返回栈的容量即2m
    explicit operator int() const noexcept override;	   		//返回栈的实际元素个数
    Stack& operator<<(int e) override; 	     		//将e入栈，并返回当前栈
    Stack& operator>>(int& e) override;     		//出栈到e，并返回当前栈
    Stack& operator=(const Stack& s);	//深拷贝赋值并返回被赋值栈
    Stack& operator=(Stack&& s)noexcept;//移动赋值并返回被赋值栈
    char* print(char* b)const noexcept override;	//从栈底到栈顶打印栈元素
    ~Stack()noexcept override;	              	//销毁栈
};

class StackFull : std::exception {
public:
    [[nodiscard]] const char * what() const noexcept override {
        return "Stack is full";
    }
};

class StackEmpty : std::exception {
public:
    [[nodiscard]] const char * what() const noexcept override {
        return "Stack is empty";
    }
};

#endif //EX3_STACK_H
