#ifndef TCOLORPC_H
#define TCOLORPC_H

#include<stdio.h>

enum tColorPC_type
{
    TCOLORPC_UNSELECT=-1,

    TCOLORPC_METHOD_NORMAL=0,
    TCOLORPC_METHOD_HIGHLIGHT,
    TCOLORPC_METHOD_UNDERLINE,
    TCOLORPC_METHOD_REVERSE,

    TCOLORPC_FR_BLACK=30,
    TCOLORPC_FR_RED,
    TCOLORPC_FR_GREEN,
    TCOLORPC_FR_ORANGE,
    TCOLORPC_FR_BLUE,
    TCOLORPC_FR_purple,
    TCOLORPC_FR_CYAN,
    TCOLORPC_FR_GREY,

    TCOLORPC_BK_BLACK=40,
    TCOLORPC_BK_RED,
    TCOLORPC_BK_GREEN,
    TCOLORPC_BK_ORANGE,
    TCOLORPC_BK_BLUE,
    TCOLORPC_BK_PURPLE,
    TCOLORPC_BK_CYAN,
    TCOLORPC_BK_GREY,
};


struct tColor
{
    enum tColorPC_type method;
    enum tColorPC_type foreColor;
    enum tColorPC_type backColor;
};

extern void printColor(struct tColor *tcolor);

#define TCOLORPC_P_NORMAL "\033[0m"
#define TCOLORPC_P_FR_GREEN  "\033[32m"
#define TCOLORPC_P_FR_ORANGE "\033[33m"


#endif //TCOLORPC_H
