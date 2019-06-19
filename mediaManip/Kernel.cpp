#include "Kernel.h"
#include <cmath>

using namespace std;

Kernel::Kernel(int m, int n) : m{m}, n{n}, vals(new float[m * n]) 
{
    for (int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            set(i, j, f(i, j));
}

void Kernel::fillKernel(Kernel * k)
{
    float s = 0;
    float a = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            a = k->f(i, j);
            s += a;
            set(i, j, a);
        }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            set(i, j, get(i, j) / s);

}

void Kernel::apply(Image& im)
{
    im.quantizeColorSpace( RGBColorspace );
    for (int i = 1; i < im.columns() - 1; i++)
    {
        for (int j = 1; j < im.rows() - 1; j++)
        {
        ColorRGB a(0, 0, 0);
        ColorRGB b;
            for (int k = 0; k < m; k++)
                for(int l = 0; l < n; l++)
                {
                    b = im.pixelColor(i + k - (m - m%2) / 2, j + l - (n - n%2) / 2);
                    a.red(a.red() + b.red() * get(k, l));
                    a.green(a.green() + b.green() * get(k, l));
                    a.blue(a.blue() + b.blue() * get(k, l));
                }
        im.pixelColor(i, j, a);
        }
    }
}

float Kernel::f(float x, float y)
{
    if (x == (m - 1) / 2 && y == (n - 1) / 2) return 1;
    else return 0;
}


float Gaussian::f(float x, float y)
{
    return 1 / sqrt(2 * M_PI) * exp(-pow((x + y - (n - n%2)), 2) / 2);
}


float CircleBlur::f(float x, float y)
{
    return sqrt(pow((x - (m - m%2)), 2) + pow((y - (n - n%2)), 2));
}
