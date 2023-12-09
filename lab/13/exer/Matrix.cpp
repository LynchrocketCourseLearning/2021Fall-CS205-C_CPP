#include <cstdlib>
#include <iostream>
#include <string>

template<typename T>
class Matrix
{
private:
    size_t row;
    size_t col;
    T* data;
public:
    Matrix(size_t, size_t);
    ~Matrix();

    Matrix& operator+(Matrix&);
    Matrix& operator*(Matrix&);
    Matrix& operator+=(Matrix&);

    T & operator()(size_t, size_t, T);
    T operator()(size_t, size_t) const;

    void print();
};

template<typename T>
Matrix<T>::Matrix(size_t row, size_t col)
{
    this->row = row;
    this->col = col;
    this->data = new T[row * col];
    if(this->data == NULL)
    {
        std::cerr << "Fail to create Matrix" << '\n';
        return;
    } 
}

template<typename T>
Matrix<T>::~Matrix()
{
   delete[] this->data;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+(Matrix& a)
{
    if(this->data == NULL || a.data == NULL) 
    {
        std::cerr << "Null matrix for addition" << '\n';
        exit(1);
    }
    if(this->row != a.row || this->col != a.col)
    {
        std::cerr << "Not matched for addition" << '\n';
        exit(1);
    }
    size_t len = this->col * this->row;
    Matrix<T> * res = new Matrix<T>(this->row, this->col);
    for (size_t i = 0; i < len; ++i)
    {
        res->data[i] = this->data[i] + a.data[i];
    }
    return *res;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*(Matrix& a)
{
    if(this->data == NULL || a.data == NULL) 
    {
        std::cerr << "Null matrix for multiplication" << '\n';
        exit(1);
    }
    Matrix * res = new Matrix<T>(this->row, a.col);
    for (size_t i = 0; i < this->row; ++i)
    {
        for (size_t k = 0; k < a.row; ++k)
        {    
            T tmp = this->data[i*this->col+k];
            for (size_t j = 0; j < a.col; ++j)
            {  
                res->data[i*this->col+j] = tmp * a.data[k*a.col+j];
            }
        }
    }
    return *res;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(Matrix& a)
{
    if(this->data == NULL || a.data == NULL) 
    {
        std::cerr << "Null matrix for addition-equation" << '\n';
        exit(1);
    }
    size_t len = this->col * this->row;
    for (size_t i = 0; i < len; ++i)
    {
        this->data[i] += a.data[i];
    }
    return *this;
}

template<typename T>
T & Matrix<T>::operator()(size_t r, size_t c, T val)
{
    if(r >= this->row || c >= this->col)
    {
        std::cerr << "out of range" << '\n';
        exit(1);
    }

    this->data[r*this->col+c] = val;

    return this->data[r*this->col+c];
}

template<typename T>
T Matrix<T>::operator()(size_t r, size_t c) const
{
    if(r >= this->row || c >= this->col)
    {
        std::cerr << "out of range" << '\n';
        exit(1);
    }

    return this->data[r*this->col+c];
}

template<typename T>
void Matrix<T>::print()
{
    for (size_t i = 0; i < this->row; ++i)
    {
        for (size_t j = 0; j < this->col; ++j)
        {
           std::cout << this->data[i*this->col+j] << " " ;
        }
        std::cout << '\n';
    }
}


