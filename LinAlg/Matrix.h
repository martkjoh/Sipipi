#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;


// An object describing the shape of a matrix an M * N matrix has s.m = M, s.n = N

struct Shape
{
    int m;
    int n;

    bool operator==(const Shape &rhs) {return m == rhs.m && n == rhs.n;}
};

class Matrix
{
    private:
        Shape s;
        float* data;

    public:
        Matrix(Shape s, float fill = 0);
        Matrix(int m, int n, float fill = 0);
        Matrix(int m, int n, float* data);
        Matrix();
        Matrix(const Matrix &other);
        ~Matrix();

        Matrix operator+=(const Matrix &rhs);
        Matrix operator-=(Matrix rhs);
        Matrix operator- ();
        Matrix operator*= (const Matrix &rhs);
        Matrix operator= (Matrix rhs);
        float * operator[](int i);


        void print();
        int size();
        float getVal(int i, int j) const;
        Shape shape() const;
        float absMax() const;
        Matrix T() const;
};



// Helper functions for matrices
//
// Functions to use on matrices for manipulation, analysis etc...

// Opperators to use on Matrices

Matrix operator* (Matrix lhs, const Matrix &rhs);
Matrix operator+ (Matrix lhs, const Matrix &rhs);
Matrix operator- (Matrix lhs, const Matrix &rhs);


// Fucntions for solving Ax = b

void LU(Matrix &A);
Matrix jacobi(Matrix M, const Matrix &b, Matrix x0, float tol = 1e-10);
Matrix SOR(Matrix A, Matrix b, Matrix x0, float w, float tol = 10e-10);
Matrix gaussSeidel(Matrix A, Matrix b, Matrix x0, float tol = 1e-10);


// Functions for manipulating and generating matrices

Matrix splitLU(Matrix &U);
Matrix rand(int M, int N, float min = 0, float max = 1);
Matrix randDiag(int M, int N, float min = 0, float max = 1);


