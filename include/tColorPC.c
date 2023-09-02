#include "tColorPC.h"

void printColor(struct tColor *tcolor)
{
    int flag = 0;
    if(tcolor->method == -1)flag += 1;
    if(tcolor->foreColor == -1)flag += 2;
    if(tcolor->backColor == -1)flag += 4;
    switch (flag) {
        case 0:
            printf("\033[%d;%d;%dm",tcolor->method,tcolor->foreColor,tcolor->backColor);
            break;
        case 1:
            printf("\033[%d;%dm",tcolor->foreColor,tcolor->backColor);
            break;
        case 2:
            printf("\033[%d;%dm",tcolor->method,tcolor->backColor);
            break;
        case 4:
            printf("\033[%d;%dm",tcolor->method,tcolor->foreColor);
            break;
        case 3:
            printf("\033[%dm",tcolor->backColor);
            break;
        case 5:
            printf("\033[%dm",tcolor->foreColor);
            break;
        case 6:
            printf("\033[%dm",tcolor->method);
            break;
    }
}

