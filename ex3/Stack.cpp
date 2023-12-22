//
// Created by cassius on 2023/10/2.
//

#include "Stack.h"

Stack::Stack(int m) : Queue(m), q(m) {}

Stack::Stack(const Stack &s) : Queue((Queue&)s), q(s.q) {}

Stack::Stack(Stack &&s) noexcept : Queue((Queue&&)s), q((Queue&&)s.q) {}

int Stack::size() const noexcept {
    return Queue::size() + q.size();
}

Stack::operator int() const noexcept {
    return Queue::operator int() + int(q);
}

Stack &Stack::operator<<(int e) {
    if(Queue::operator int() < Queue::size() - 1){
        Queue::operator<<(e);
        return *this;
    }
    else if(int(q) < q.size() - 1){
        int tmp;
        Queue::operator>>(tmp);
        q<<tmp;
        Queue::operator<<(e);
        return *this;
    }
    else{
        throw StackFull();
    }
}

Stack &Stack::operator>>(int &e){
    int tmp;
    if(Queue::operator int()){
        int len = Queue::operator int();
        for(int i=0;i<len-1;i++){
            // 循环len-1次，这样需要出栈的元素就在队尾了，然后直接出队就可以了。
            Queue::operator>>(tmp);
            Queue::operator<<(tmp);
        }
        Queue::operator>>(e);
        return *this;
    }
    else if(int(q)){
        int len = q.operator int();
        for(int i=0;i<len-1;i++){
            q>>tmp;
            q<<tmp;
        }
        q>>e;
        return *this;
    }
    else{
        throw StackEmpty();
    }
}

Stack &Stack::operator=(const Stack &s) {
    Queue::operator=((Queue&)s);
    q.operator=((Queue&)s.q);
    return *this;
}

Stack &Stack::operator=(Stack &&s) noexcept {
    Queue::operator=((Queue&&)s);
    q.operator=((Queue&&)s.q);
    return *this;
}

char * Stack::print(char *b) const noexcept {
    std::string s = "";  // 先随便摆一个空字符串在这里。
    s = Queue::print(s);
    b = q.print(b);
    strcat(b, s.c_str());
    return b;
}
Stack::~Stack() noexcept {
//    Queue::~Queue();
//    q.~Queue();
}
