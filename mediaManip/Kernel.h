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

    protected:
        // The (x,y) coords are for the kernel, the (p,q) coords are for the picture
        virtual float f(float x, float y, float p = 0, float q = 0);
        virtual float get(int x, int y, float p = 0, float q = 0) {return f(x, y, p, q);}

    public:
        Kernel();
        Kernel(int m, int n) : m{m}, n{n} {}

        int columns() {return 2*m + 1;}
        int rows() {return 2*n + 1;}
        // Sets origo in the center insted of top left corner
        int yCoord(int y) {return y - m;}
        int xCoord(int x) {return x - n;}
        
        Image apply(Image& im, Kernel * ker);
};

class StaticKernel : public Kernel
{
    private:
        float* vals;

    protected:
        virtual float f(float x, float y, float p = 0, float q = 0) {return 0;}
        void fillKernel(Kernel * k);
        float get(int x, int y, float p, float q) {return vals[x + y*rows()];}
        void set(int x, int y, float v) {vals[x + y*rows()] = v;}

    public:
        ~StaticKernel() {delete[] vals;}
        StaticKernel(int m, int n, Kernel * k) : Kernel(m, n) {fillKernel(k);}

        void print();
};

class Gaussian : public StaticKernel
{
    private:
        float f(float x, float y);
        float s;

    public:
        Gaussian(int n, float s = 1) :s{s}, StaticKernel(n, n, this) {}
};


// class Edge : public StaticKernel
// {
//     private: 
//         float f(float x, float y);

//     public:
//         Edge(int n) : StaticKernel(n, n, this) {}
// };

// class Sharpen : public StaitcKernel
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