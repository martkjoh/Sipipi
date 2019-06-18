#include <Magick++.h>

using namespace Magick;


void makeCoolImage()
{
    int n = 500;
    Image test(Geometry(n, n), "white");

    Pixels pxCache(test);
    Quantum* px;
    px = pxCache.get(0, 0, n, n);
    float a, b, c;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            a = (i * j) / (n * n * 1.);
            b = (i * (n - j)) / (n * n * 1.);
            c = ((n - 1) * j) / (n * n * 1.);
            test.pixelColor(i, j, ColorRGB(1 - a, b, c));
        }

    test.write("CoolImage.png");
}