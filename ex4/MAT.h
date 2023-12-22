//
// Created by cassius on 2023/10/12.
//

#ifndef EX4_MAT_H
#define EX4_MAT_H
#include <iomanip>
#include <exception>
#include <typeinfo>
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>

template <typename T>
class MAT {
private:
    T* const e; // 指向所有整型矩阵元素的指针
    const int r, c;  // 矩阵的行r和列c
public:
    MAT(int r, int c);   // 矩阵定义
    MAT(const MAT& a);
    MAT(MAT&& a) noexcept;
    virtual ~MAT() noexcept;
    virtual T* const operator[](int r);  // 取出矩阵第一个元素的地址
    virtual MAT operator+(const MAT& a) const;  // 矩阵加法，不能加抛出异常
    virtual MAT operator-(const MAT& a) const;  // 矩阵减法，不能减抛出异常
    virtual MAT operator*(const MAT& a) const;  // 矩阵乘法，不能乘抛出异常
    virtual MAT operator~() const;  // 矩阵转置
    virtual MAT& operator=(const MAT& a);  // 深拷贝赋值运算
    virtual MAT& operator=(MAT&& a) noexcept;  // 移动赋值运算
    virtual MAT& operator+=(const MAT& a);  // += 运算
    virtual MAT& operator-=(const MAT& a);  // -=运算
    virtual MAT& operator*=(const MAT& a);  // *= 运算
    virtual char* print(char* s) const noexcept; // print输出至s，列用空格隔开，行用回车结束。
};

template<typename T>
MAT<T>::MAT(int r, int c) :r(r), c(c), e(new T[r * c]) {}

template<typename T>
MAT<T>::MAT(const MAT& a) : e(new T[a.r * a.c]), r(a.r), c(a.c) {
    for (int i = 0; i < r * c; i++) {
        e[i] = a.e[i];
    }
}

template<typename T>
MAT<T>::MAT(MAT&& a) noexcept : e(a.e), r(a.r), c(a.c) {
    *(T*)&(a.c) = 0;
    *(T*)&(a.r) = 0;
    *(T**)&(a.e) = nullptr;
}

template<typename T>
MAT<T>::~MAT() noexcept {
    delete[] e;
    *(T**)&e = nullptr;
    *(int*)&r = 0;
    *(int*)&c = 0;
}

template<typename T>
T* const MAT<T>::operator[](int r) {
    if (r < this->r && r >= 0) {
        return &e[r * c];
    }
    else {
        throw "Operator[] ERROR!";
    }
}

template<typename T>
MAT<T> MAT<T>::operator+(const MAT& a) const {
    if (r == a.r && c == a.c) {
        MAT result(r, c);
        for (int i = 0; i < r * c; i++) {
            result.e[i] = e[i] + a.e[i];
        }
        return result;
    }
    throw "Operator+ ERROR!";
}

template<typename T>
MAT<T> MAT<T>::operator-(const MAT& a) const {
    if (r == a.r && c == a.c) {
        MAT result(r, c);
        for (int i = 0; i < r * c; i++) {
            result.e[i] = e[i] - a.e[i];
        }
        return result;
    }
    throw "Operator- ERROR!";
}

template<typename T>
MAT<T> MAT<T>::operator*(const MAT& a) const {
    if (c == a.r) {
        MAT result(r, a.c);
        MAT &aa = (MAT&)a;
        MAT &siht = (MAT&) *this;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < a.r; j++) {
                result[i][j] = 0;
                for (int k = 0; k < c; k++) {
                    result[i][j] += siht[i][k] * aa[k][j];
                }
            }
        }
        return result;
    }
    throw "Operator* ERROR!";
}

template<typename T>
MAT<T> MAT<T>::operator~() const {
    MAT result(c, r);
    for (int i = 0; i < this->r; i++) {
        for (int j = 0; j < c; j++) {
            result.e[j*r+i] = e[i * c + j];
            // result[j][i] = (*this)[i][j];
        }
    }
    return result;
}

template<typename T>
MAT<T>& MAT<T>::operator=(const MAT& a) {
    if (this != &a) {
        delete[] e;
        *(T**)&e = new T[r * c];
        for (int i = 0; i < r * c; i++) {
            e[i] = a.e[i];
        }
        *(int*)&r = a.r;
        *(int*)&c = a.c;
    }
    return *this;
}

template<typename T>
MAT<T>& MAT<T>::operator=(MAT&& a) noexcept {
    if (this != &a) {
        delete[] e;
        *(T**)&e = a.e;
        *(int*)&r = a.r;
        *(int*)&c = a.c;

        *(T**)&a.e = nullptr;
        *(int*)&a.c = 0;
        *(int*)&a.r = 0;
        return *this;
    }
    else {
        return *this;
    }
}

template<typename T>
MAT<T>& MAT<T>::operator+=(const MAT& a) {
    if (r == a.r && c == a.c) {
        for (int i = 0; i < r * c; i++) {
            e[i] += a.e[i];
        }
        return *this;
    }
    throw "Operator+= ERROR!";
}

template<typename T>
MAT<T>& MAT<T>::operator-=(const MAT& a) {
    if (r == a.r && c == a.c) {
        for (int i = 0; i < r * c; i++) {
            e[i] -= a.e[i];
        }

        return *this;
    }
    throw "Operator-= ERROR!";

}

template<typename T>
MAT<T>& MAT<T>::operator*=(const MAT& a) {
    if (c == a.r) {
        MAT result(r, a.c);
        MAT &aa = (MAT&)a;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < a.c; j++) {
                result[i][j] = 0;
                for (int k = 0; k < c; k++) {
//                    result[i][j] += e[i * c + k] * a.e[k * c + j];
                     result[i][j] += (*this)[i][k] * aa[k][j];
                }
            }
        }
        *this = (MAT&&)result;
        return *this;
    }
    throw "Operator*= ERROR!";
}

template<typename T>
char* MAT<T>::print(char* s) const noexcept {
    std::ostringstream oss;
//    if (typeid(e[0]) == typeid(int) || typeid(e[0]) == typeid(long) || typeid(e[0]) == typeid(long long) ||
//        typeid(e[0]) == typeid(float) || typeid(e[0]) == typeid(double)) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (j != 0) {
                oss << " ";
            }
            oss << std::setw(6) << e[i * c + j];
            if (j == c - 1) {
                oss << "\n";
            }
        }
    }
//    }
    strcpy(s, oss.str().c_str());
    return s;
}

class MatMulError : std::exception{
        const char * what() const noexcept override{
            return "Operator*= ERROR!";
        }
    };

#endif //EX4_MAT_H

