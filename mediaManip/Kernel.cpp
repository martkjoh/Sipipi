#include "Kernel.h"
#include <cmath>

using namespace std;

Kernel::Kernel(int m, int n) : m{m}, n{n}, vals(new float[(2*m+1) * (2*n+1)]) 
{
    for (int i = 0; i < rows(); i++)
        for (int j = 0; j < columns(); j++)
            set(i, j, f(xCoord(i), yCoord(j)));
}

void Kernel::fillKernel(Kernel * k)
{
    float s = 0;
    float a = 0;
    for (int i = 0; i < rows(); i++)
        for (int j = 0; j < columns(); j++)
        {
            a = k->f(xCoord(i), yCoord(j));
            s += a;
            set(i, j, a);
        }

    for (int i = 0; i < rows(); i++)
        for (int j = 0; j < columns(); j++)
        if (s != 0)
            set(i, j, get(i, j) / s);
}

Image Kernel::apply(Image& im)
{
    im.quantizeColorSpace( RGBColorspace );
    Image im2(im);
    for (int i = 1; i < im.rows() - 1; i++)
    {
        for (int j = 1; j < im.columns() - 1; j++)
        {

        // Color of new pizel
        ColorRGB a(0, 0, 0);
        // Color of old pixel
        ColorRGB b;
            for (int k = 0; k < rows(); k++)
                for(int l = 0; l < columns(); l++)
                {
                    b = im.pixelColor(j + xCoord(l), i + yCoord(k));
                    a.red(a.red() + b.red() * get(l, k));
                    a.green(a.green() + b.green() * get(l, k));
                    a.blue(a.blue() + b.blue() * get(l, k));
                }
        im2.pixelColor(j, i, a);
        }
    }
    return im2;
}

void Kernel::print()
{
    for (int i = 0; i < columns(); i++)
    {
        for(int j = 0; j < rows(); j++)
        cout << vals[i * columns() + j] << "     ";
    cout << endl;
    }
}

float Kernel::f(float x, float y)
{
    if (x == 0 && y == 0)  return 1;
    else return 0;
}

float Gaussian::f(float x, float y)
{
    return 1 / sqrt(2 * M_PI) / s * exp(-(x*x + y*y) / (2*s*s));
}


float Edge::f(float x, float y)
{
    if (x == 0 && y == 0) return rows() * columns() - 1;
    else return -1;
}

float Sharpen::f(float x, float y)
{
    if (x == 1 && y == 1) return 5;
    if ((x == 0 && y == 0) ||
        (x == 0 && y == 2) ||
        (x == 2 && y == 0) ||
        (x == 2 && y == 2))
        return -1;
    else return 0;
}

float Smear::f(float x, float y)
{
    return 1 / sqrt(2 * M_PI) / s 
    * exp(-(x*x) / (2*s*s));
}
