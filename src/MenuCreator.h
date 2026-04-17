#ifndef __MENU_CREATOR_H__
#define __MENU_CREATOR_H__

#include "Defines.h"
#include "string.h"
#include <Arduino.h>
#include <LiquidCrystal.h>
#define MAX_CHILD 10
#define MENU_MODE 1
#define IDEL 2
class MenuCreator
{
private:
    MenuCreator *childrens[MAX_CHILD];
    char buffer[20];
    short max_child_count;
    int index;
    MenuCreator *Pernat;
    MenuCreator *current;
    void (*triggerFun)(void);
    static LiquidCrystal lcd;
    static int UP, DOWN, OK, BACK;
    static short ROW, COL;
    static int IP_MODE;
    static bool mode;

public:
    MenuCreator();

    static void init();

    static void idealText(char idealMsg[4][20]);
    int appendChild(MenuCreator *child);
    void attachCallBack(void (*callback)(void));
    void butProcess();
    MenuCreator &operator<<(const char *text);
};

#endif