#include <iostream>
#include "MAT.h"
int main0() {
    MAT<int> a(1,2), b(2,2), c(1,2);
    char buffer[4096];
    a[0][0] = 1;
    a[0][1] = 2;
    std::cout<<"matrix a:"<<std::endl;
    std::cout<<a.print(buffer)<<std::endl;
    b[0][0] = 3;
    b[0][1] = 4;
    b[1][0] = 5;
    b[1][1] = 6;
    std::cout<<"matrix b:"<<std::endl;
    std::cout<<b.print(buffer)<<std::endl;
    c = a * b;
    std::cout<<"matrix c=a*b:"<<std::endl;
    std::cout<<c.print(buffer)<<std::endl;
    std::cout<<"matrix a+c:"<<std::endl;
    std::cout<<(a+c).print(buffer)<<std::endl;
    c = c-a;
    std::cout<<"matrix c=c-a:"<<std::endl;
    std::cout<<c.print(buffer)<<std::endl;
    std::cout<<"matrix c+=a:"<<std::endl;
    std::cout<<(c+=a).print(buffer)<<std::endl;
    c = ~a;
    std::cout<<"matrix c=~a:"<<std::endl;
    std::cout<<c.print(buffer)<<std::endl;
    MAT<double> d(2,2),e(2,2);
    d[0][0] = 3.5;
    d[0][1] = 4.5;
    d[1][0] = 5.5;
    d[1][1] = 6.5;
    e[0][0] = 3.3;
    e[0][1] = 4.3;
    e[1][0] = 5.3;
    e[1][1] = 6.3;
    std::cout<<"matrix d+e:"<<std::endl;
    std::cout<<(d+e).print(buffer)<<std::endl;
    return 0;
}

class MyFloat{
private:
    int integer;
    float decimal;
public:
    MyFloat() : integer(0), decimal(0.0f){}
    MyFloat(float x) : integer(int(x)), decimal(x-integer){}
    MyFloat(int i, float d) : integer(i), decimal(d){}
    // Overload + operator
    MyFloat operator+(const MyFloat &other) const {
        float result = float(integer) + decimal + float(other.integer) + other.decimal;
        return MyFloat(result);
    }

    // Overload - operator
    MyFloat operator-(const MyFloat &other) const {
        float result = float(integer) + decimal - (float(other.integer) + other.decimal);
        return MyFloat(result);
    }

    // Overload * operator
    MyFloat operator*(const MyFloat &other) const {
        float result = (float(integer) + decimal) * (float(other.integer) + other.decimal);
        return MyFloat(result);
    }

    // Overload / operator
    MyFloat operator/(const MyFloat &other) const {
        if (other.integer == 0 && other.decimal == 0) {
            // Handle division by zero
            return MyFloat(0, 0.0f);
        }

        float result = (float(integer) + decimal) / (float(other.integer) + other.decimal);
        return MyFloat(result);
    }

    // Overload = operator
    MyFloat &operator=(const MyFloat &other) {
        if (this != &other) {
            integer = other.integer;
            decimal = other.decimal;
        }
        return *this;
    }
    // Overloaded += operator
    MyFloat& operator+=(const MyFloat& other) {
        *this = *this + other;
        return *this;
    }

    // Overloaded -= operator
    MyFloat& operator-=(const MyFloat& other) {
        *this = *this - other;
        return *this;
    }

    // Overloaded *= operator
    MyFloat& operator*=(const MyFloat& other) {
        *this = *this * other;
        return *this;
    }

    // Overloaded /= operator
    MyFloat& operator/=(const MyFloat& other) {
        *this = *this / other;
        return *this;
    }
    [[nodiscard]] float toFloat() const {
        return static_cast<float>(integer) + decimal;
    }
    friend std::ostream& operator<<(std::ostream& os, const MyFloat& obj) {
        os << obj.toFloat();
        return os;
    }
};


int main(){
    MAT<MyFloat> a(1,2), b(2,2), c(1,2),d(2,2);
    a[0][0] = 1.5;
    a[0][1] = 2.5;
    b[0][0] = 3.5;
    b[0][1] = 4.5;
    b[1][0] = 5.5;
    b[1][1] = 6.5;
    c = a*b;
    std::cout<<"matrix c=a*b:"<<std::endl;
    char buffer[100];
    std::cout<<c.print(buffer)<<std::endl;
    return 0;
}

