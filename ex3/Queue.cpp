//
// Created by cassius on 2023/10/2.
//

#include "Queue.h"

Queue::Queue(int m) : elems(new int[m]), max(m), head(0), tail(0) {}

Queue::Queue(const Queue &q) : elems(new int[q.max]), max(q.max) {
    this->head = q.head;
    this->tail = q.tail;
    for(int i=q.head;i!=q.tail;i=(i+1)%max){
        this->elems[i] = q.elems[i];
    }
}

Queue::Queue(Queue &&q) noexcept : elems(q.elems), max(q.max){
    this->head = q.head;
    this->tail = q.tail;
    for(int i=q.head;i!=q.tail;i=(i+1)%max){
        this->elems[i] = q.elems[i];
    }
    q.head = q.tail = 0;
    *((int**)&(q.elems)) = nullptr;
    *((int*)&(q.max)) = 0;
}

Queue::operator int() const noexcept {
    return max==0 ? 0 : (tail+max-head)%max;
}

int Queue::size() const noexcept {
    return this->max;
}

Queue &Queue::operator<<(int e) {
    if((this->tail+1)%this->max == this->head){
        throw QueueFull();
    }
    this->elems[this->tail] = e;
    this->tail = (this->tail+1)%this->max;
    return *this;
}

Queue &Queue::operator>>(int &e) {
    if(this->tail == this->head){
        throw QueueEmpty();
    }
    e = this->elems[head];
    this->head = (this->head+1)%this->max;
    return *this;
}

Queue &Queue::operator=(const Queue &q) {  // 为什么赋值运算符不声明为virtual呢？
    if(this == &q){
        return *this;
    }
    *((int**)&(this->elems)) = new int[q.max];
    *((int*)&(this->max)) = q.max;
    this->head = q.head;
    this->tail = q.tail;
    for(int i=q.head;i<=q.tail;i++){
        this->elems[i%q.max] = q.elems[i%q.max];
    }
    return *this;
}

Queue &Queue::operator=(Queue &&q) noexcept {
    if(this == &q){
        return *this;
    }
    delete[] this->elems;
    *((int**)&(this->elems)) = q.elems;
    this->head = q.head;
    this->tail = q.tail;
    *((int*)&(this->max)) = q.max;

    q.head = q.tail = 0;
    *((int**)&(q.elems)) = nullptr;
    *((int*)&(q.max)) = 0;
    return *this;
}

char *Queue::print(char *s) const noexcept {  // 实验二中的print函数，也为了给Stack来重载，保留
    std::ostringstream oss;  // 使用oss，这样的话就可以对于任意大小的队列都可以执行打印了。
    for(int i=this->head;i!=tail;i=(i+1)%max){
        oss<<this->elems[i]<<",";
    }
    std::string result = oss.str();
    strcpy(s,result.c_str());
    return s;
}

std::string Queue::print(std::string& s) const noexcept {  // 为了方便Stack那边的打印，这里就不再return char*，而是直接return string类型了
    std::ostringstream oss;  // 使用oss，这样的话就可以对于任意大小的队列都可以执行打印了。
    for(int i=this->head;i!=tail;i=(i+1)%max){
        oss<<this->elems[i]<<",";
    }
    std::string result = oss.str();
    s = result;
    return s;
}

Queue::~Queue() {
    if(this->elems != nullptr){
        delete[] this->elems;
        this->head = this->tail = 0;
        *((int**)&(this->elems)) = nullptr;
        *((int*)&(this->max)) = 0;
    }
}
