//
// Created by cassius on 2023/10/2.
//

#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
class Queue{
private:
    int* const  elems;	//elems申请内存用于存放队列的元素
    const  int  max;	//elems申请的最大元素个数为max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
public:
    explicit Queue(int m);		//初始化队列：最多申请m个元素
    Queue(const Queue& q); 			//用q深拷贝初始化队列
    Queue(Queue&& q)noexcept;		//用q移动初始化队列
    virtual explicit operator int() const noexcept;	//返回队列的实际元素个数
    [[nodiscard]] virtual int size() const noexcept;		//返回队列申请的最大元素个数max
    virtual Queue& operator<<(int e);  	//将e入队列尾部，并返回当前队列
    virtual Queue& operator>>(int& e); 	//从队首出元素到e，并返回当前队列
    Queue& operator=(const Queue& q);//深拷贝赋值并返回被赋值队列
    Queue& operator=(Queue&& q)noexcept;//移动赋值并返回被赋值队列
    virtual char* print(char *s) const noexcept;//在实验二中的，并且为了给Queue重写的方法，保留
    std::string print(std::string& s) const noexcept;//打印队列至s并返回s,为了方便Stack那边调用，直接保留string的方法
    virtual ~Queue();	 					//销毁当前队列
};

// 自己添加的异常处理
class QueueEmpty : public std::exception {
public:
    [[nodiscard]] const char * what() const noexcept override {
        return "Queue is empty";
    }
};

class QueueFull : public std::exception {
public:
    [[nodiscard]] const char * what() const noexcept override {
        return "Queue is full";
    }
};
#endif //EX3_QUEUE_H
