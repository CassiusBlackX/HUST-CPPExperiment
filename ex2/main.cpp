#include <iostream>
#include "QUEUE.h"

int main0() {
    QUEUE q1(16);
    q1<<1<<2<<3<<4<<5<<6;
    QUEUE q2(5);
    q2 = q1;
    std::cout<<"int(q1):"<<int(q1)<<std::endl;
    std::cout<<"int(q2):"<<int(q2)<<std::endl;
    std::cout<<"q1.size():"<<q1.size()<<" q2.size():"<<q2.size()<<std::endl;
    int a;
    for(int i=0;i<6;i++){
        q2>>a;
        std::cout<<a<<" ";
    }
    return 0;
}










int main(){
    QUEUE q(5);
    q<<1<<2<<3<<4;
    std::cout<<"q.size():"<<q.size()<<" int(q):"<<int(q)<<std::endl;
    int a;
    for(int i=0;i<4;i++){
        q>>a;
    }
    std::cout<<"q.size():"<<q.size()<<" int(q):"<<int(q)<<std::endl;
    q>>a;
}