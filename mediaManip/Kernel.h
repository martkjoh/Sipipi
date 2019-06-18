#include <Magick++.h>
#include <iostream>

using namespace Magick;


class Kernel
{
    private:
        int m, n;

    protected:
        float* vals;

    public:
        Kernel(int m, int n);

        void apply(Image& im);
        float get(int x, int y){return vals[m * x + y];}
        void set(int x, int y, float v){vals[m * x + y] = v;}
        void set(float* v);
};

class Gaussian : public Kernel
{
    public:
        Gaussian();
};