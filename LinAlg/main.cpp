#include "Matrix.h"

int main()
{
    srand(time(nullptr));
    int n = 10;
    Matrix A = randDiag(n, n, 0, 10);
    Matrix b = rand(n, 1);
    Matrix x0 = rand(n, 1);
    Matrix x{n, 1};

    for (double i = 0; i < 20; i++)
    {
        x = SOR(A, b, x0, i / 10);
        cout << (A * x - b).absMax() << endl;
    }
    
    return 0;
}