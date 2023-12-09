#include "matrix.hpp"
#include "cal.hpp"

template<typename T>
matrix<T>::matrix(size_t row, size_t col, size_t channel) {
    this->row = row;
    this->col = col;
    this->channel = channel;
    this->val = new T[row * col * channel];
    this->refcount = 1;
}

template<typename T>
matrix<T>::matrix(size_t row, size_t col, size_t channel, std::ifstream &f) {
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    this->row = row;
    this->col = col;
    this->val = new T[row * col * channel];
    for (size_t i = 0; i < row * channel; ++i) {
        std::string l;
        std::getline(f, l, '\n');
        std::stringstream ssl(l);
        for (size_t j = 0; j < col; ++j) {
            ssl >> this->val[i * row + j];
        }
    }
    f.clear();
}

template<typename T>
matrix<T>::matrix(const matrix &ma) {
    this = ma;
    this->refcount++;
}

template<typename T>
matrix<T>::~matrix() {
    if (this == NULL || this->val == NULL) return;
    if (this->refcount > 1) this->refcount--;
    else delete[] this->val;
}

template<typename T>
size_t matrix<T>::get_row() const {
    if (this == NULL) {
        std::cerr << "ERROR: Matrix referred is NULL!" << '\n';
        throw std::invalid_argument("Matrix referred is NULL!");
    }
    return this->row;
}

template<typename T>
size_t matrix<T>::get_col() const {
    if (this == NULL) {
        std::cerr << "ERROR: Matrix referred is NULL!" << '\n';
        throw std::invalid_argument("Matrix referred is NULL!");
    }
    return this->col;
}

template<typename T>
T *matrix<T>::get_val() const {
    if (this == NULL) {
        std::cerr << "ERROR: Matrix referred is NULL!" << '\n';
        throw std::invalid_argument("Matrix referred is NULL!");
    }
    return this->val;
}

template<typename T>
T matrix<T>::at(size_t i, size_t j) {
    if (this == NULL || this->val == NULL) {
        std::cerr << "ERROR: Invalid matrix!" << '\n';
        throw std::invalid_argument("Invalid matrix!");
    }
    return this->val[i * this->col + j];
}

template<typename T>
matrix<T> &matrix<T>::operator+(const matrix<T> &ma) {
    if (this == NULL) {
        std::cerr << "ERROR: Matrix referred is NULL!" << '\n';
        throw std::invalid_argument("Matrix referred is NULL!");
    }
    if (this->row != ma.get_row() || this->col != ma.get_col()) {
        std::cerr << "ERROR: Not match for addition!" << '\n';
        throw std::invalid_argument("Not match for addition!");
    }
    for (size_t i = 0; i < this->row; ++i)
        for (size_t j = 0; j < this->col; ++j)
            this->val[i * this->col + j] += ma.val[i * this->col + j];
    return *this;
}

template<typename T>
matrix<T> &matrix<T>::operator-(const matrix<T> &ma) {
    if (this == NULL) {
        std::cerr << "ERROR: Matrix referred is NULL!" << '\n';
        throw std::invalid_argument("Matrix referred is NULL!");
    }
    if (this->row != ma.get_row() || this->col != ma.get_col()) {
        std::cerr << "ERROR: Not match for subtraction!" << '\n';
        throw std::invalid_argument("Not match for subtraction!");
    }
    for (size_t i = 0; i < this->row; ++i)
        for (size_t j = 0; j < this->col; ++j)
            this->val[i * this->col + j] -= ma.val[i * this->col + j];
    return *this;
}

template<typename T>
matrix<T> &operator*(matrix<T> &ma, const T b) {
    if (ma.val == NULL) {
        std::cerr << "ERROR: Matrix referred is NULL!" << '\n';
        throw std::invalid_argument("Matrix referred is NULL!");
    }
    for (size_t i = 0; i < ma.row; ++i)
        for (size_t j = 0; j < ma.col; ++j)
            ma.val[i * ma.col + j] *= b;
    return ma;
}

template<typename T>
matrix<T> &matrix<T>::operator=(const matrix<T> &ma) {
    if (this == NULL) {
        std::cerr << "ERROR: Matrix referred is NULL!" << '\n';
        throw std::invalid_argument("Matrix referred is NULL!");
    }
    if (this == &ma) return *this;
    this->row = ma.row;
    this->col = ma.col;
    this->val = ma.val;
    return *this;
}

template<typename T>
bool matrix<T>::operator==(const matrix<T> &ma) {
    if (this == NULL) {
        std::cerr << "ERROR: Matrix referred is NULL!" << '\n';
        throw std::invalid_argument("Matrix referred is NULL!");
    }
    if (this->row != ma.get_row() || this->col != ma.get_col())
        return false;
    for (size_t i = 0; i < this->row; ++i)
        for (size_t j = 0; j < this->col; ++j)
            if (this->val[i * this->col + j] != ma.val[i * this->col + j]) return false;
    return true;
}

template<typename T>
bool matrix<T>::operator!=(const matrix<T> &ma) {
    if (this == NULL) {
        std::cerr << "ERROR: Matrix referred is NULL!" << '\n';
        throw std::invalid_argument("Matrix referred is NULL!");
    }
    if (this->row != ma.get_row() || this->col != ma.get_col())
        return true;
    for (size_t i = 0; i < this->row; ++i)
        for (size_t j = 0; j < this->col; ++j)
            if (this->val[i * this->row + j] != ma.val[i * this->row + j]) return true;
    return false;
}

template<typename T>
void matrix<T>::multiply(const matrix<T> &ma, const matrix<T> &mb, int mode) {
    if (this == NULL) return;
    if (this->col != ma.get_row()) {
        std::cerr << "ERROR: Not match for multiplication!" << '\n';
        throw std::invalid_argument("Not match for multiplication!");
    }
    switch (mode) {
        case 1://simple
            simple(*this, ma, mb);
            break;
        case 2://simd
            simd(*this, ma, mb);
            break;
        case 3://blas
            blas(*this, ma, mb);
            break;
        default:
            std::cerr << "ERROR: invalid mode!" << '\n';
            throw std::invalid_argument("invalid mode!");
    }
}

template<typename T>
void matrix<T>::show() {
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    for (size_t i = 0; i < this->row; ++i) {
        for (size_t j = 0; j < this->col; ++j) {
            std::cout << this->val[i * this->col + j];
            if (j != this->col) std::cout << ", ";
        }
        std::cout << ';' << '\n';
    }
}