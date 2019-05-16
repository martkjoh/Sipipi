#include "Matrix.h"


Matrix::Matrix(Shape s, double fill) : s{s},  data{new double[s.n * s.m]}
{
    for (int i = 0; i < size(); i++) {data[i] = fill;}
}

Matrix::Matrix(int m, int n, double fill) : Matrix{Shape{m, n}, fill} {}
Matrix::Matrix(int m, int n, double* data) : s{m, n} {swap(this->data, data);}
Matrix::Matrix() : Matrix(0, 0) {}

Matrix::Matrix(const Matrix &other) : s{other.s}, data{new double[s.n * s.m]}
{
    for (int i = 0; i < size(); i++) {data[i] = other.data[i];}
}
Matrix::~Matrix() {delete[] data;}


double * Matrix::operator[](int i) {return &data[s.n * i];}

Matrix Matrix::operator*=(const Matrix &rhs)
{
    if (this->s.n != rhs.s.m) {throw "incompatible dimensions";}

    Matrix A(this->s.m, rhs.s.n);
    for (int i = 0; i < this->s.m; i++)
    {
        for (int j = 0; j < rhs.s.n; j++)
        {
            double s = 0;
            for (int k = 0; k < this->s.m; k++) {s += this->getVal(i, k) * rhs.getVal(k, j);}
            A[i][j] = s;
        }
    }
    return A;
}

Matrix Matrix::operator-=(const Matrix &rhs)
{
    if (!(this->shape() == rhs.shape())) {throw "Incompatible dimensions";}
    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++) {(*this)[i][j] -= rhs.getVal(i, j);}
    }
    return *this;
}

void Matrix::print()
{
    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++)
        {
            cout << (*this)[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


int Matrix::size() {return s.m * s.n;}

double Matrix::getVal(int i, int j) const {return data[j + this->s.n * i];}

Shape Matrix::shape() const {return s;}


// Opperators to use on Matrices

Matrix operator* (Matrix lhs, const Matrix &rhs) {return lhs *= rhs;}


// Helper functions for matrices

void LU(Matrix &A)
{
    if (A.shape().m != A.shape().m) {throw "Nonsquare Marix";}

    for (int i = 0; i < A.shape().m - 1; i++)
    {
        for (int j = i + 1; j < A.shape().m; j++)
        {
            A[j][i] /= A[i][i];
            for (int k = i + 1; k < A.shape().n; k++)
            {
                A[j][k] -= A[j][i] * A[i][k];
            }
        }
    }
}


Matrix splitLU(Matrix &U)
{
    Matrix L{U.shape()};
    for (int i = 0; i < U.shape().m; i++)
    {
        L[i][i] = 1;
        for (int j = 0; j < i; j++)
        {
            L[i][j] = U[i][j];
            U[i][j] = 0;
        }
    }
    return L;
}
