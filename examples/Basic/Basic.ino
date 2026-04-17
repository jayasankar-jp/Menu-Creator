
#include <MenuCreator.h>
LiquidCrystal MenuCreator::lcd(12, 11, 5, 4, 3, 2); // example pins

int MenuCreator::UP = 8;
int MenuCreator::DOWN = 9;
int MenuCreator::OK = 10;
int MenuCreator::BACK = 13;
int MenuCreator::IP_MODE = LOW; // LOW TRIGGER
short MenuCreator::COL = 16;
short MenuCreator::ROW = 2;

MenuCreator root;
MenuCreator Menu1;
MenuCreator Menu2;
MenuCreator Menu3;
MenuCreator Menu4;
MenuCreator Menu5;

void fun4()
{

    Serial.println("Fun 4 executed");
}
void fun2()
{

    Serial.println("Fun 2 executed");
}
void fun3()
{

    Serial.println("Fun 3 executed");
}
void fun5()
{

    Serial.println("Fun 5 executed");
}
void setup()
{
    Serial.begin(9600);
    MenuCreator::init();

    root.appendChild(&Menu1);
    root.appendChild(&Menu2);
    root.appendChild(&Menu3);
    Menu1.appendChild(&Menu4);
    Menu1.appendChild(&Menu5);
    Menu1 << "Menu1";
    Menu2 << "Menu2";
    Menu3 << "Menu3";
    Menu4 << "Menu4";
    Menu5 << "Menu5";
    Menu2.attachCallBack(fun2);
    Menu3.attachCallBack(fun3);
    Menu4.attachCallBack(fun4);
    Menu5.attachCallBack(fun5);
}
void loop()
{
    root.butProcess();
}
