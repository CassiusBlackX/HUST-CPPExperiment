#include <iostream>
#include "Stack.h"
int main0() {
    Stack s1(10);
    s1 << 1 << 2 << 3 << 4 << 5;
    char buffer[100];
    s1.print(buffer);
    std::cout<<"s1:"<<buffer<<std::endl;
    Stack s2(s1);
    s2.print(buffer);
    std::cout<<"s2:"<<buffer<<std::endl;
    std::cout<<"s1.size():"<<s1.size()<<" s2.size():"<<s2.size()<<std::endl;
    std::cout<<"int(s1):"<<int(s1)<<" int(s2):"<<int(s2)<<std::endl;
    Stack s3(16);
    int top;
    s2>>top;
    std::cout<<"s2 top:"<<top<<std::endl;
    s3 = s2;
    s3.print(buffer);
    std::cout<<"s3:"<<buffer<<std::endl;
    std::cout<<"s2.size():"<<s2.size()<<" int(s2):"<<int(s2)<<" s3.size():"<<s3.size()<<" int(s3):"<<int(s3)<<std::endl;
    s3<<5<<6<<7<<8<<9;
    s3.print(buffer);
    std::cout<<"s3:"<<buffer<<std::endl;
    s3<<10<<11;
    std::cout<<"s3:"<<s3.print(buffer)<<std::endl;
    std::cout<<"int(s3):"<<int(s3)<<" s3.size():"<<s3.size()<<std::endl;
    s3<<12<<13<<14<<15<<16;
    std::cout<<"s3:"<<s3.print(buffer)<<std::endl;
    std::cout<<"int(s3):"<<int(s3)<<" s3.size():"<<s3.size()<<std::endl;
    Stack s4 = std::move(s2);
    std::cout<<"s4:"<<s4.print(buffer)<<"\ns2:"<<s2.print(buffer)<<std::endl;
    std::cout<<"s4.size():"<<s4.size()<<" int(s4):"<<int(s4)<<"\ns2.size():"<<s2.size()<<" int(s2):"<<int(s2)<<std::endl;
    Stack s5(5);
    s5<<1<<2<<3<<4;
    std::cout<<s1.print(buffer)<<std::endl;
    std::cout<<"s1.size():"<<s5.size()<<" int(s1):"<<int(s5)<<std::endl;
    std::cout<<"\n";
    s1<<5;
    std::cout<<s5.print(buffer)<<std::endl;
    std::cout<<"s1.size():"<<s5.size()<<" int(s1):"<<int(s5)<<std::endl;
    s5<<6;
    std::cout<<s5.print(buffer)<<std::endl;
    std::cout<<"s1.size():"<<s5.size()<<" int(s1):"<<int(s5)<<std::endl;
    return 0;
}


int main() {
    Stack s(4);
    s<<1<<2<<3<<4<<5;
    std::cout<<"s.size():"<<s.size()<<" int(s):"<<int(s)<<std::endl;
    s<<6;
    std::cout<<"s.size():"<<s.size()<<" int(s):"<<int(s)<<std::endl;
    int a;
    for(int i=0;i<6;i++) {
        s >> a;
    }
    std::cout<<"int(s)"<<int(s)<<std::endl;
    s>>a;
}