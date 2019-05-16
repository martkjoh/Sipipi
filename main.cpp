
#include <iostream>
#include "Matrix.h"
#include "Classes.h"'

using namespace std;

int main()
{

    Dog d(4);
    cout << d.getAge() << endl;
    // int n = 2000;
    // Matrix A(n, n);
    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < n; j++) {A[i][j] = rand() % 10 + 1;}
    // }
    
    // // Matrix B(A);
    // cout << "start" << endl;
    // LU(A);
    // cout << "done" << endl;
    // // Matrix L = splitLU(A);
    // // (L * A -= B).print();

    return 0;
}