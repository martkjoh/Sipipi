#include "Kernel.h"
#include <iostream>

using namespace std;

int main()
{   
    Image im("blomst.jpeg");

    Gaussian g(2);
    g.print();
    im = g.apply(im);
    im.write("hehe.jpeg");
    return 0;
}