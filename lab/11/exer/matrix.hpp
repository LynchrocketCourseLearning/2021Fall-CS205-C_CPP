#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

class Matrix
{
    public:
        size_t row;
        size_t col;
        float* val;
        Matrix():row(0),col(0),val(NULL){};
        Matrix(size_t row, size_t col):row(row),col(col),val(new float[row*col]{0}){};
        Matrix(size_t row, size_t col, float val):row(row),col(col){
            this->val = new float[row*col];
            for(int i = 0; i < row*col; ++i) this->val[i] = val;
        };
        Matrix(Matrix&);
        ~Matrix();
        Matrix& operator+(const Matrix&);
        Matrix& operator+(const float);
        Matrix& operator-(const Matrix&);
        Matrix& operator=(const Matrix&);
        friend Matrix& operator*(Matrix&, const float);

        void show();
};

Matrix::Matrix(Matrix& ma)
{
    this->row = ma.row;
    this->col = ma.col;
    this->val = new float[this->row * this->col];
    for(int i  = 0; i < this->row*this->col; ++i)
        this->val[i] = ma.val[i];
}

Matrix::~Matrix()
{
    if(this != NULL && this->val != NULL)
    {
        delete[] this->val;
        this->val = NULL;
    }
}

Matrix& Matrix::operator+(const Matrix& ma)
{
    if(this==NULL||&ma==NULL||this->val==NULL||ma.val==NULL) return *this;
    if(this->row!=ma.row||this->col!=ma.col) return *this;
    for(int i = 0; i < this->row; ++i)
    {
        for(int j = 0; j < this->col; ++j)
        {
            this->val[i*this->col+j]+=ma.val[i*this->col+j];
        }
    }
    return *this;
}

Matrix& Matrix::operator+(const float a)
{
    for(int i = 0; i < this->row; ++i)
        for(int j = 0; j < this->col; ++j)
            this->val[i*this->col+j]+=a;
    return *this;
}

Matrix& Matrix::operator-(const Matrix& ma)
{
    if(this==NULL||&ma==NULL||this->val==NULL||ma.val==NULL) return *this;
    if(this->row!=ma.row||this->col!=ma.col) return *this;
    for(int i = 0; i < this->row; ++i)
        for(int j = 0; j < this->col; ++j)
            this->val[i*this->col+j]-=ma.val[i*ma.col+j];
    return *this;
}

Matrix& Matrix::operator=(const Matrix& ma)
{
    if(this==NULL||&ma==NULL)return *this;
    if(this!=&ma)
    {
        delete[] this->val;
        this->row = ma.row;
        this->col = ma.col;
        this->val = new float[this->row*this->col];
        for(int i  = 0; i < this->row*this->col; ++i)
            this->val[i] = ma.val[i];
    }
    return *this;
}

Matrix& operator*(Matrix& ma,const float a)
{
    if(&ma==NULL||ma.val==NULL) return ma;
    for(int i = 0; i < ma.row; ++i)
        for(int j = 0; j < ma.col; ++j)
            ma.val[i*ma.col+j]*=a;
    return ma;
}

void Matrix::show()
{
    cout<<this->val<<endl;
    for(int i = 0; i < this->row; ++i)
    {
         for(int j = 0; j < this->col; ++j)
        {
            cout << this->val[i*this->col+j];
            if(j!=this->col-1) cout << ", ";
        }
        cout << ';' << '\n';
    }
}