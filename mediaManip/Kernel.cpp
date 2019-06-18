#include "Kernel.h"

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
                    b = im.pixelColor(i + k - (m - 1) / 2, j + l - (n - 1) / 2);
                    a.red(a.red() + b.red() * get(k, l));
                    a.green(a.green() + b.green() * get(k, l));
                    a.blue(a.blue() + b.blue() * get(k, l));
                }
        im.pixelColor(i, j, a);
        }
    }
}

Kernel::Kernel(int m, int n) : m{m}, n{n}, vals(new float[m * n]) {}

void Kernel::set(float* v)
{
    for (int i = 0; i < m * n; i++)
        vals[i] = v[i];
}


// Gaussian::Gaussian() : Kernel(3, 3)
// {
//     float v [] = {
//         1 / 16., 2 / 16., 1 / 16.,
//         2 / 16., 4 / 16., 2 / 16.,
//         1 / 16., 2 / 16., 1 / 16.};

//     set(v);
// }


Gaussian::Gaussian() : Kernel (5, 5)
{
    float v [] = {
        1 / 273.,   4 / 273.,    7 / 273.,   4 / 273.,  1 / 273.,

        4 / 273.,   16 / 273.,   26 / 273.,  16 / 273., 4 / 273.,

        7 / 273.,   26 / 273.,   41 / 273.,  26 / 273., 7 / 273.,

        4 / 273.,   16 / 273.,   26 / 273.,  16 / 273., 4 / 273.,

        1 / 273.,   4 / 273.,    7 / 273.,   4 / 273.,  1 / 273.,};


    set(v);
}