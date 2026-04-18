#ifndef __MENU_CREATOR_H__
#define __MENU_CREATOR_H__

#include "Defines.h"
#include "string.h"
#include <Arduino.h>
#include <LiquidCrystal.h>
#define MAX_CHILD 10
#define MENU_MODE 1
#define IDEAL 2
class MenuCreator
{
private:
    MenuCreator *childrens[MAX_CHILD];
    char buffer[20];
    short max_child_count;
    int index;
    MenuCreator *Pernat;
    static MenuCreator *current;
    static MenuCreator *rootNode;
    void (*triggerFun)(void);
    static LiquidCrystal lcd;
    static int UP, DOWN, OK, BACK;
    static short ROW, COL;
    static int IP_MODE;
    static short mode;
    static unsigned long initial_time_ref;
    static unsigned long timeout;
    static char idealMsg[4][20];

public:
    MenuCreator();

    static void init();
    static void setRoot(MenuCreator *root);
    static void setIdealText(int line, char msg[20]);
    static void butProcess();
    int appendChild(MenuCreator *child);
    void attachCallBack(void (*callback)(void));

    MenuCreator &operator<<(const char *text);
};

#endif