#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>

#include <iostream>
#include <iomanip>
#include <chrono>
#include <unistd.h>

#include "matrix.hpp"

#define TIMER Timer stopwatch;

void check_file(std::ifstream &);

size_t read_row(std::ifstream &);

size_t read_col(std::ifstream &);

template<typename T>
void from_file(matrix<T> &ma, const size_t row, const size_t col, std::ifstream & f){
    T s;
    for (size_t i = 0; i < row; ++i) {
        std::string l;
        std::getline(f, l, '\n');
        std::stringstream ssl(l);
        for (size_t j = 0; j < col; ++j) {
            ssl >> s;
            ma.set(i, j, s);
        }
    }
    f.clear();
}

template<typename T>
void to_file(const matrix<T> &ma, std::ofstream &f){
    size_t row = ma.get_row();
    size_t col = ma.get_col();
    T tmp;
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            f << std::setiosflags(std::ios::fixed) << std::setprecision(8) << ma.get_val()[i * col + j] << ' ';
        }
        f << '\n';
    }
    f.clear();
}

class Timer {
private:
    std::chrono::time_point<std::chrono::system_clock> start_;
    constexpr static auto unit_ =
            static_cast<double>(std::chrono::microseconds::period::num)
            / std::chrono::microseconds::period::den;
public:
    Timer() {
        this->start_ = std::chrono::system_clock::now();
    }

    ~Timer() {
        auto end = std::chrono::system_clock::now();
        std::cout << "Time spent: " << std::setiosflags(std::ios::fixed) << std::setprecision(8)
                  << static_cast<double>((end - this->start_).count()) * unit_
                  << " sec" << '\n';
    }
};


template<typename T>
class complex {
private:
    T re;
    T im;
public:
    complex() : re(0), im(0) {};

    complex(T re, T im) : re(re), im(im) {};

    complex<T> &operator+(const complex<T> &b) {
        if (this == NULL) {
            std::cerr << "ERROR: Complex referred is NULL!" << '\n';
            throw std::invalid_argument("Complex referred is NULL!");
        }
        this->re += b.re;
        this->im += b.im;
        return *this;
    }

    complex<T> &operator-(const complex<T> &b) {
        if (this == NULL) {
            std::cerr << "ERROR: Complex referred is NULL!" << '\n';
            throw std::invalid_argument("Complex referred is NULL!");
        }
        this->re -= b.re;
        this->im -= b.im;
        return *this;
    }

    complex<T> &operator*(const complex<T> &b) {
        if (this == NULL) {
            std::cerr << "ERROR: Complex referred is NULL!" << '\n';
            throw std::invalid_argument("Complex referred is NULL!");
        }
        this->re = this->re * b.re - this->im * b.im;
        this->im = this->im * b.re + this->re * b.im;
        return *this;
    }

    complex<T> &operator/(const complex<T> &b) {
        if (this == NULL) {
            std::cerr << "ERROR: Complex referred is NULL!" << '\n';
            throw std::invalid_argument("Complex referred is NULL!");
        }
        T base = sqrt(b.re * b.re + b.im * b.im);
        this->re = (this->re * b.re + this->im * b.im) / base;
        this->im = (this->im * b.re - this->re * b.im) / base;
        return *this;
    }

    bool operator==(const matrix<T> &b) {
        if (this == NULL) {
            std::cerr << "ERROR: Complex referred is NULL!" << '\n';
            throw std::invalid_argument("Complex referred is NULL!");
        }
        return (this->re == b.re && this->im == b.im);
    }

    bool operator!=(const matrix<T> &b) {
        if (this == NULL) {
            std::cerr << "ERROR: Complex referred is NULL!" << '\n';
            throw std::invalid_argument("Complex referred is NULL!");
        }
        return !this->operator==(b);
    }

    void show() {
        std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
        if (this == NULL) {
            std::cerr << "ERROR: Complex referred is NULL!" << '\n';
            throw std::invalid_argument("Complex referred is NULL!");
        }
        if (this->im == 0) std::cout << this->re << '\n';
        if (this->im < 0) std::cout << this->re << '-' << abs(this->im) << '\n';
        if (this->im > 0) std::cout << this->re << '+' << abs(this->im) << '\n';
    }
};