#include "MenuCreator.h"
short MenuCreator::mode = IDEL;
unsigned long MenuCreator::initial_time_ref = 0;
MenuCreator *MenuCreator::current = nullptr;
MenuCreator *MenuCreator::rootNode = nullptr;
MenuCreator::MenuCreator()
{
    Pernat = nullptr;

    triggerFun = nullptr;
    max_child_count = 0;

    for (int i = 0; i < MAX_CHILD; i++)
    {
        childrens[i] = nullptr;
    }
    index = -1;
}

void MenuCreator::setRoot(MenuCreator *root)
{
    if (current == nullptr)
    {
        current = root;
        rootNode = root;
        current->index = 0;
    }
}
int MenuCreator::appendChild(MenuCreator *child)
{
    if (max_child_count >= MAX_CHILD)
    {
        return -1;
    }
    childrens[max_child_count] = child;
    max_child_count++;
    // Serial.print("Current :");
    // Serial.println(max_child_count);
    child->Pernat = this;
    return 1;
}

MenuCreator &MenuCreator::operator<<(const char *text)
{
    strncpy(buffer, text, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0'; // safety null termination
    return *this;                      // allow chaining
}
void MenuCreator::init()
{
    lcd.begin(COL, ROW);
    lcd.clear();
    pinMode(UP, IP_MODE == LOW ? INPUT_PULLUP : INPUT);
    pinMode(DOWN, IP_MODE == LOW ? INPUT_PULLUP : INPUT);
    pinMode(OK, IP_MODE == LOW ? INPUT_PULLUP : INPUT);
    pinMode(BACK, IP_MODE == LOW ? INPUT_PULLUP : INPUT);
}
void MenuCreator::attachCallBack(void (*callback)(void))
{
    triggerFun = callback;
}
void MenuCreator::idealText(char idealMsg[4][20])
{
    for (int i = 0; i < ROW; i++)
    {
        lcd.setCursor(0, i);
        lcd.print(idealMsg[i]);
    }
}
void MenuCreator::butProcess()
{
    static bool is_press = 0;
    if (current)
    {
        if (digitalRead(UP) == IP_MODE && is_press == 0)
        {
            is_press = 1;

            lcd.clear();
            if (mode == MENU_MODE)
            {
                if (current->index < current->max_child_count - 1)
                    current->index = current->index + 1;
            }
            Serial.print("Current : ");
            Serial.println(current->index);
            lcd.setCursor(0, 0);
            lcd.print(">");
            lcd.print(current->childrens[current->index]->buffer);
            if (current->index < current->max_child_count)
            {
                lcd.setCursor(0, 1);
                lcd.print("  ");
                lcd.print(current->childrens[current->index + 1]->buffer);
            }

            mode = MENU_MODE;
            delay(100);
        }
        else if (digitalRead(DOWN) == IP_MODE && is_press == 0)
        {
            is_press = 1;
            lcd.clear();
            if (mode == MENU_MODE)
            {
                if (current->index > 0)
                    current->index = current->index - 1;
            }
            lcd.setCursor(0, 0);
            lcd.print(">");
            lcd.print(current->childrens[current->index]->buffer);
            if (current->index < current->max_child_count)
            {
                lcd.setCursor(0, 1);
                lcd.print("  ");
                lcd.print(current->childrens[current->index + 1]->buffer);
            }

            mode = MENU_MODE;
            delay(100);
        }
        else if (digitalRead(OK) == IP_MODE && is_press == 0)
        {
            is_press = 1;
            lcd.clear();
            if (mode == MENU_MODE)
            {
                Serial.print("Index : ");
                Serial.println(current->index);
                current = current->childrens[current->index];
                current->index = 0;

                lcd.setCursor(0, 0);
                lcd.print(">");
                lcd.print(current->childrens[current->index]->buffer);

                if (current->max_child_count == 0)
                {
                    lcd.clear();
                    if (current->triggerFun != nullptr)
                        current->triggerFun();
                    current = rootNode;
                    current->index = 0;
                }
                else
                {
                    if (current->triggerFun != nullptr)
                        current->triggerFun();
                    if (current->index < current->max_child_count)
                    {
                        lcd.setCursor(0, 1);
                        lcd.print("  ");
                        lcd.print(current->childrens[current->index + 1]->buffer);
                    }
                    else
                    {
                        lcd.setCursor(0, 1);
                        lcd.print("                        ");
                    }
                }
            }
            delay(100);
            mode = MENU_MODE;
        }
        else if (digitalRead(BACK) == IP_MODE && is_press == 0)
        {
            is_press = 1;
            lcd.clear();
            if (mode == MENU_MODE)
            {
                if (current->Pernat != nullptr)
                {
                    current = current->Pernat;
                    current->index = 0;
                    if (mode == MENU_MODE)
                    {
                        if (current->index > 0)
                            current->index = current->index - 1;
                    }
                    lcd.setCursor(0, 0);
                    lcd.print(">");
                    lcd.print(current->childrens[current->index]->buffer);
                    if (current->index < current->max_child_count)
                    {
                        lcd.setCursor(0, 1);
                        lcd.print("  ");
                        lcd.print(current->childrens[current->index + 1]->buffer);
                    }
                }
            }
            delay(100);
        }
        else if (is_press == 1 && digitalRead(UP) != IP_MODE && digitalRead(DOWN) != IP_MODE && digitalRead(OK) != IP_MODE && digitalRead(BACK) != IP_MODE)
        {
            is_press = 0;
            delay(100);
        }
    }
}