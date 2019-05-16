#include <iostream>

using namespace std;


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
        double* data;

    public:
        Matrix(Shape s, double fill = 0);
        Matrix(int m, int n, double fill = 0);
        Matrix(int m, int n, double* data);
        Matrix();
        Matrix(const Matrix &other);
        ~Matrix();

        Matrix operator-=(const Matrix &rhs);
        double * operator[](int i);
        Matrix operator*= (const Matrix &rhs);


        void print();
        int size();
        double getVal(int i, int j) const;
        Shape shape() const;
};


// Opperators to use on Matrices

Matrix operator* (Matrix lhs, const Matrix &rhs);


// Helper functions for matrices

void LU(Matrix &A);
Matrix splitLU(Matrix &U);
