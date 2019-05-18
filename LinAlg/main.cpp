#include "Matrix.h"

int main()
{
    srand(time(nullptr));
    int n = 10;
    Matrix A = randDiag(n, n, 0, 10);
    Matrix b = rand(n, 1);
    Matrix x0 = rand(n, 1);
    Matrix x{n, 1};

    // Matrix x0 = rand(6, 1);
    // Matrix b{6, 1, new float[6] {
    //     5./2., 3./2, 1., 1., 3./2, 5./2.
    // }};
    // Matrix A{6, 6, new float[6 * 6] {
    //     3, -1, 0, 0, 0, 0.5,
    //     -1, 3, -1, 0, 0.5, 0,
    //     0, -1, 3, -1, 0, 0,
    //     0, 0, -1, 3, -1, 0,
    //     0, 0.5, 0, -1, 3, -1,
    //     0.5, 0, 0, 0, -1, 3,
    //     } };
    // Matrix x{6, 1};


    for (double i = 0; i < 20; i++)
    {
        x = SOR(A, b, x0, i / 10);
        cout << (A * x - b).absMax() << endl;

    }
    return 0;
}