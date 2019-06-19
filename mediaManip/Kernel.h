#include <Magick++.h>
#include <iostream>
#include <string>

using namespace Magick;
using namespace std;

class Kernel
{
    protected:
        float* vals;
        int m, n;


    public:
        Kernel() {};
        Kernel(int m, int n);
        ~Kernel() {delete[] vals;}

        virtual float f(float x, float y);
        void fillKernel(Kernel * k);
        void apply(Image& im);
        float get(int x, int y){return vals[m * x + y];}
        void set(int x, int y, float v){vals[m * x + y] = v;}
};

class Gaussian : public Kernel
{
    private:
        float f(float x, float y);

    public:
        Gaussian(int n) :Kernel(n, n) {fillKernel(this);}
};

class CircleBlur : public Kernel
{
    private: 
        float f(float x, float y);

    public:
        CircleBlur(int n) : Kernel(n, n) {fillKernel(this);}
};