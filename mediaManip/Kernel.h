#include <Magick++.h>
#include <iostream>
#include <string>

using namespace Magick;
using namespace std;

class Kernel
{
    private:
        // The kernel will have size 2m+1 x 2n+1
        int m, n;

    public:
        // The (x,y) coords are for the kernel, the (p,q) coords are for the picture
        virtual float f(float x, float y, float p = 0, float q = 0) {return 0;};
        virtual float get(int x, int y, float p = 0, float q = 0) {return f(x, y, p, q);}

        Kernel(int m, int n) : m{m}, n{n} {}

        int columns() {return 2*m + 1;}
        int rows() {return 2*n + 1;}
        // Sets origo in the center insted of top left corner
        int yCoord(int y) {return y - m;}
        int xCoord(int x) {return x - n;}
        
        Image apply(Image& im, Kernel * ker);

        virtual void test() {cout << "Helt øverst";}
};

class StaticKernel : public Kernel
{
    private:
        float* vals;

    protected:
        virtual float f(float x, float y) {return 1;}
        float get(int x, int y, float p = 0, float q = 0) {return vals[x + y*rows()];}
        void set(int x, int y, float v) {vals[x + y*rows()] = v;}

        void fillKernel(Kernel * k);

    public:
        StaticKernel(int m, int n, Kernel * k) : Kernel(m, n) {fillKernel(k); cout << typeid(*this).name() << endl;}
        ~StaticKernel() {delete[] vals;}

        virtual void test() {cout << "Basis" << endl;}
        void print();
};

class Gaussian : public StaticKernel
{
    private:
        float s;
        float f(float x, float y) 
            {return 1 / sqrt(2 * M_PI) / s * exp(-(x*x + y*y) / (2*s*s));}

    public:
        void test() override {cout << "Derived" << endl;}
        Gaussian(int n, float s = 1) : s{s}, StaticKernel(n, n, this) {cout << typeid(*this).name() << endl;}
};

// class Edge : public StaticKernel
// {
//     private: 
//         float f(float x, float y);

//     public:
//         Edge(int n) : StaticKernel(n, n, this) {}
// };

// class Sharpen : public StaticKernel
// {
//     private: 
//         float f(float x, float y);

//     public:
//         Sharpen(int n) :  StaticKernel(3, 3, this) {}
// };


// // TODO: fix this 

// class Smear : public StaticKernel
// {
//     private: 
//         float f(float x, float y);
//         float s;
//     public:
//         Smear(int n, float s = 1) : s{s},  StaticKernel(0, n, this) {}
// };