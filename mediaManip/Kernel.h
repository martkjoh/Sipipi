#include <Magick++.h>
#include <iostream>
#include <string>

using namespace Magick;
using namespace std;

class Kernel
{
    private:
        float* vals;
        // The kernel will have size 2m+1 x 2n+1
        int m, n;

    protected:
        virtual float f(float x, float y);
        void fillKernel(Kernel * k);
        float get(int x, int y) {return vals[x + y*rows()];}
        void set(int x, int y, float v) {vals[x + y*rows()] = v;}


    public:
        Kernel() {};
        Kernel(int m, int n);
        ~Kernel() {delete[] vals;}

        int columns() {return 2*m + 1;}
        int rows() {return 2*n + 1;}
        // Sets origo in the center insted of top left corner
        int yCoord(int y) {return y - m;}
        int xCoord(int x) {return x - n;}
        void print();

        Image apply(Image& im);
};

class Gaussian : public Kernel
{
    private:
        float f(float x, float y);
        float s;

    public:
        Gaussian(int n, float s = 1) :s{s}, Kernel(n, n) {fillKernel(this);}
};


class Edge : public Kernel
{
    private: 
        float f(float x, float y);

    public:
        Edge(int n) : Kernel(n, n) {fillKernel(this);}
};

class Sharpen : public Kernel
{
    private: 
        float f(float x, float y);

    public:
        Sharpen(int n) : Kernel(3, 3) {fillKernel(this);}
};


// TODO: fix this 

class Smear : public Kernel
{
    private: 
        float f(float x, float y);
        float s;
    public:
        Smear(int n, float s = 1) : s{s}, Kernel(0, n) {fillKernel(this);}
};