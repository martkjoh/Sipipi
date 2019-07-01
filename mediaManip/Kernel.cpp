#include "Kernel.h"
#include <cmath>

using namespace std;

Image Kernel::apply(Image& im)
{
    im.quantizeColorSpace( RGBColorspace );
    Image im2(im);
    for (int i = m; i < im.rows() - m; i++)
    {
        for (int j = n; j < im.columns() - n; j++)
        {

        // Color of new pizel
        ColorRGB a(0, 0, 0);
        // Color of old pixel
        ColorRGB b;
            for (int k = 0; k < rows(); k++)
                for(int l = 0; l < columns(); l++)
                {
                    b = im.pixelColor(j + xCoord(l), i + yCoord(k));
                    a.red(a.red() + b.red() * this->get(l, k));
                    a.green(a.green() + b.green() * this->get(l, k));
                    a.blue(a.blue() + b.blue() * this->get(l, k));
                }
        im2.pixelColor(j, i, a);
        }
    }
    return im2;
}


void StaticKernel::fillKernel()
{
    cout << typeid(*this).name() << endl;
    float s = 0;
    float a = 0;
    for (int i = 0; i < rows(); i++)
        for (int j = 0; j < columns(); j++)
        {
            a = this->f(xCoord(j), yCoord(i));
            s += a;
            set(i, j, a);
        }

    for (int i = 0; i < rows(); i++)
        for (int j = 0; j < columns(); j++)
        if (s != 0)
            set(i, j, get(i, j) / s);
}

void StaticKernel::print()
{
    for (int i = 0; i < columns(); i++)
    {
        for(int j = 0; j < rows(); j++)
        cout << vals[i * columns() + j] << "     ";
    cout << endl;
    }
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

// float Smear::f(float x, float y)
// {
//     return 1 / sqrt(2 * M_PI) / s 
//     * exp(-(x*x) / (2*s*s));
// }
