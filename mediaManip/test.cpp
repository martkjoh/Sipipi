#include "Kernel.h"
#include <iostream>

using namespace std;

int main()
{   
    Image im("blomst.jpeg");

    int n = 5;
    CircleBlur g(n);
    g.apply(im);
    for (int i = 0; i < n; i++)
        {
        for (int j = 0; j < n; j++)
            cout << g.get(i, j) << "     ";
        cout << endl;
        }

    im.write("hehe.jpeg");
    return 0;
}