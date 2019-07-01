#include "Kernel.h"
#include <iostream>

using namespace std;

int main()
{   
    Image im("blomst.jpeg");

    StaticKernel g;
    g.print();
    im = g.apply(im);
    im.write("hehe.jpeg");
    return 0;
}