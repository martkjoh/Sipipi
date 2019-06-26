#include "Kernel.h"
#include <iostream>

using namespace std;

int main()
{   
    Image im("blomst.jpeg");

    Gaussian g(1, 1);
    g.print();
    im = g.apply(im, &g);

    // Edge e(1);
    // e.print();
    // im = e.apply(im);
    // Sharpen s(3);
    // im = s.apply(im);
    // Smear s(3, 10);
    // s.print();
    // im = s.apply(im);   

    im.write("hehe.jpeg");
    return 0;
}