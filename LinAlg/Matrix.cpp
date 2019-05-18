#include "Matrix.h"


Matrix::Matrix(Shape s, float fill) : s{s},  data{new float[s.n * s.m]}
{
    for (int i = 0; i < size(); i++) {data[i] = fill;}
}

Matrix::Matrix(int m, int n, float fill) : Matrix{Shape{m, n}, fill} {}
Matrix::Matrix(int m, int n, float* data) : s{m, n} {swap(this->data, data);}
Matrix::Matrix() : Matrix(0, 0) {}

Matrix::Matrix(const Matrix &other) : s{other.s}, data{new float[s.n * s.m]}
{
    for (int i = 0; i < size(); i++) {data[i] = other.data[i];}
}
Matrix::~Matrix() {delete[] data;}


float * Matrix::operator[](int i) {return &data[s.n * i];}

Matrix Matrix::operator*=(const Matrix &rhs)
{
    if (this->s.n != rhs.s.m) {throw "incompatible dimensions";}

    Matrix A(this->s.m, rhs.s.n);
    float s;
    for (int i = 0; i < this->s.m; i++)
    {
        for (int j = 0; j < rhs.s.n; j++)
        {
            s = 0;
            for (int k = 0; k < this->s.m; k++) 
            {
                s += this->getVal(i, k) * rhs.getVal(k, j);
            }
            A[i][j] = s;
        }
    }
    return A;
}

Matrix Matrix::operator+= (const Matrix &rhs)
{
    if (!(this->shape() == rhs.shape())) {throw "Incompatible dimensions";}
    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++) {(*this)[i][j] += rhs.getVal(i, j);}
    }
    return *this;
}

Matrix Matrix::operator-=(Matrix rhs)
{
    return (*this) += -rhs;
}


Matrix Matrix::operator- ()
{
    for (int i = 0; i < size(); i++)
    {
        data[i] = -data[i];
    }
    return *this;
}

Matrix Matrix::operator= (Matrix rhs)
{
    swap(rhs.data, data);
    return *this;
}


void Matrix::print()
{
    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++)
        {
            cout << setw(5) << left << setprecision(3) << (*this)[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;
}


int Matrix::size() {return s.m * s.n;}

float Matrix::getVal(int i, int j) const {return data[j + s.n * i];}

Shape Matrix::shape() const {return s;}

// Highest entry in the matrix, by absolute value
float Matrix::absMax() const
{
    float m = 0;
    for (int i = 0; i < shape().m; i++)
    {
        for (int j = 0; j < shape().n; j++)
        {
            if (abs(getVal(i, j)) > m){m = abs(getVal(i, j));}
        }
    }
    return m;
}

Matrix Matrix::T() const
{
    Matrix T{s.n, s.m};
    for (int i = 0; i < s.m; i++)
    {
        for (int j = 0; j < s.n; j++)
        {
            T[j][i] = getVal(i, j);
        }
    }
    return T;
}



// Opperators to use on Matrices

Matrix operator* (Matrix lhs, const Matrix &rhs) {return lhs *= rhs;}
Matrix operator+ (Matrix lhs, const Matrix &rhs) {return lhs += rhs;}
Matrix operator- (Matrix lhs, const Matrix &rhs) {return lhs -= rhs;}



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

Matrix jacobi(Matrix M, const Matrix &b, Matrix x0, float tol)
{
    Matrix x(x0.shape());
    Matrix DInv(M.shape());
    for (int i = 0; i < DInv.shape().m; i++)
    {
        DInv[i][i] = 1 / M[i][i];
        M[i][i] = 0;
    }

    int k = 0;
    while(true)
    {
        x = M * x0;
        x = b - x;
        x = DInv * x; 
        cout << k << endl;
        if ((x - x0).absMax() < tol) {return x;}
        x0 = x;
        k++;
    }

}

Matrix SOR(Matrix A, Matrix b, Matrix x0, float w, float tol)
{
    Matrix x{x0};
    float s = 0;
    int k = 0;
    while(true)
    {
        for(int i = 0; i < A.shape().m; i++)
        {
            s = b[i][0];
            for(int j = 0; j < A.shape().m; j++)
            {
                if (i == j){continue;}
                s -= A[i][j] * x[j][0];
            }
            x[i][0] = (1 - w) * x[i][0] + s * w / A[i][i];
        }
        k++;
        if ((x - x0).absMax() < tol) 
        {
            cout << "w = " << w << ", iteratirons = " << k << endl;
            return x;
        }
        x0 = x;
    }
}


Matrix gaussSeidel(Matrix A, Matrix b, Matrix x0, float tol)
{
    return SOR(A, b, x0, 1);
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


Matrix rand(int M, int N, float min, float max)
{
    Matrix A{M, N};
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            A[i][j] = ((float)rand() / RAND_MAX) * (max - min) + min;
        }
    }
    return A;
}

Matrix randDiag(int M, int N, float min, float max)
{
    Matrix A{M, N};
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            A[i][j] = ((float)rand() / RAND_MAX) * (max - min) + min;
        }
        A[i][i] += max * N;
    }
    return A;
}
