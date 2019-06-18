#include "Kernel.h"

int main()
{   
    Image im("blomst.jpeg");
    im.pixelColor(3, 3, "black");
    Gaussian g;
    g.apply(im);
    im.write("hehe.jpeg");
    return 0;
}