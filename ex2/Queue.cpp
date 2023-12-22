//
// Created by cassius on 2023/10/1.
//

#include "Queue.h"

QUEUE::QUEUE(int m) : elems(new int[m]), max(m), head(0), tail(0) {}

QUEUE::QUEUE(const QUEUE &q) : elems(new int[q.max]), max(q.max), head(q.head), tail(q.tail) {
    for(int i=q.head;i!=q.tail;i=(i+1)%max){
        this->elems[i] = q.elems[i];
    }
}

QUEUE::QUEUE(QUEUE &&q) noexcept : elems(q.elems), max(q.max), head(q.head), tail(q.tail) {
    q.head = q.tail = 0;
    *((int**)&(q.elems)) = nullptr;
    *((int*)&(q.max)) = 0;
}

QUEUE::operator int() const noexcept {
    return max==0 ? 0 : (tail+max-head)%max;
}

int QUEUE::size() const noexcept {
    return this->max;
}

QUEUE &QUEUE::operator<<(int e) {
    if((tail+1)%max==head){
        throw QueueFull();
    }
    this->elems[tail] = e;
    this->tail = (tail+1)%max;
    return *this;
}

QUEUE &QUEUE::operator>>(int &e) {
    if(this->tail == this->head){
        throw QueueEmpty();
    }
    e = this->elems[head];
    this->head = (head+1)%max;
    return *this;
}

QUEUE &QUEUE::operator=(const QUEUE &q) {
    if(this == &q){
        return *this;
    }
    if(this->elems != nullptr){
        delete[] this->elems;
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

QUEUE &QUEUE::operator=(QUEUE &&q) noexcept {
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

char *QUEUE::print(char *s) const noexcept {  // 为什么这里会是一个char*的返回值啊？ 明明应该直接是void函数啊！
    std::ostringstream oss;  // 使用oss，这样的话就可以对于任意大小的队列都可以执行打印了。
    for(int i=this->head;i!=tail;i=(i+1)%max){
        oss<<this->elems[i]<<",";
    }
    std::string result = oss.str();
    strcpy(s,result.c_str());
    return s;
}

QUEUE::~QUEUE() {
    if(this->elems != nullptr){
        delete[] this->elems;
        this->head = this->tail = 0;
        *((int**)&(this->elems)) = nullptr;
        *((int*)&(this->max)) = 0;
    }
}

