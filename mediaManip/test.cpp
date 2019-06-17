#include <Magick++.h>
#include <iostream>

using namespace std;
using namespace Magick;

int main()
{   
    int n = 500;
    Image test(Geometry(n, n), "white");

    Pixels pxCache(test);
    Quantum* px;
    px = pxCache.get(0, 0, n, n);
    float a;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            a = (i * j) / (n * n * 1.);
            test.pixelColor(i, j, ColorRGB(a, a / 2, 1 - a));
        }

    test.write("hello_world.png");
    return 0;
}