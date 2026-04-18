# MenuCreator

**MenuCreator** is an Arduino LCD menu library that helps you build hierarchical menu systems using push buttons and a `LiquidCrystal` display.

It is designed for fast menu creation with simple syntax, callback support, nested menus, idle screen messages, and easy navigation.

---

## ✨ Features

- 📟 Supports `LiquidCrystal` LCD displays
- 📂 Multi-level menu system
- 🔘 Button navigation (UP / DOWN / OK / BACK)
- ⚡ Callback function support
- 🧩 Easy child-parent menu linking
- 💤 Idle screen message support
- ⏱ Auto timeout to idle mode
- 🛠 Lightweight and simple API

---

## 📦 Installation

### Arduino IDE Library Manager

Search for:

```txt
MenuCreator
```

### Manual Installation

1. Download ZIP
2. Open Arduino IDE
3. Go to:

```txt
Sketch > Include Library > Add .ZIP Library
```

---

## 🔌 Supported Hardware

### Boards

- Arduino Uno
- Arduino Nano
- Arduino Mega
- ESP8266 / ESP32 (Arduino framework)
- Any Arduino-compatible board

### LCD Displays

- 16x2 LCD
- 20x4 LCD
- Any `LiquidCrystal` compatible display

---

# 🚀 Full Configuration Example

```cpp
#include <MenuCreator.h>

/* LCD Pins: RS, EN, D4, D5, D6, D7 */
LiquidCrystal MenuCreator::lcd(12, 11, 5, 4, 3, 2);

/* Button Pins */
int MenuCreator::UP    = 8;
int MenuCreator::DOWN  = 9;
int MenuCreator::OK    = 10;
int MenuCreator::BACK  = 13;

/* Trigger Mode */
int MenuCreator::IP_MODE = LOW;     // LOW = Active LOW buttons

/* LCD Size */
short MenuCreator::COL = 16;
short MenuCreator::ROW = 2;

/* Idle Timeout (seconds) */
unsigned long MenuCreator::timeout = 60;

/* Menu Objects */
MenuCreator root;
MenuCreator Menu1;
MenuCreator Menu2;
MenuCreator Menu3;
MenuCreator Menu4;
MenuCreator Menu5;

/* Callback Functions */
void fun2(){ Serial.println("Menu2 Pressed"); }
void fun3(){ Serial.println("Menu3 Pressed"); }
void fun4(){ Serial.println("Menu4 Pressed"); }
void fun5(){ Serial.println("Menu5 Pressed"); }

void setup()
{
    Serial.begin(9600);

    MenuCreator::init();
    MenuCreator::setRoot(&root);

    /* Build Menu Tree */
    root.appendChild(&Menu1);
    root.appendChild(&Menu2);
    root.appendChild(&Menu3);

    Menu1.appendChild(&Menu4);
    Menu1.appendChild(&Menu5);

    /* Menu Names */
    Menu1 << "Settings";
    Menu2 << "Status";
    Menu3 << "About";
    Menu4 << "WiFi";
    Menu5 << "Reset";

    /* Attach Functions */
    Menu2.attachCallBack(fun2);
    Menu3.attachCallBack(fun3);
    Menu4.attachCallBack(fun4);
    Menu5.attachCallBack(fun5);

    /* Idle Messages */
    MenuCreator::setIdealText(0, "Welcome");
    MenuCreator::setIdealText(1, "Select Option");
}

void loop()
{
    MenuCreator::butProcess();
}
```

---

# ⚙️ Complete Configuration Guide

## 📟 LCD Object

```cpp
LiquidCrystal MenuCreator::lcd(12,11,5,4,3,2);
```

Set LCD connection pins.

Format:

```cpp
LiquidCrystal MenuCreator::lcd(RS, EN, D4, D5, D6, D7);
```

---

## 🔘 Button Pins

```cpp
int MenuCreator::UP    = 8;
int MenuCreator::DOWN  = 9;
int MenuCreator::OK    = 10;
int MenuCreator::BACK  = 13;
```

Assign button input pins.

| Button | Function        |
| ------ | --------------- |
| UP     | Previous menu   |
| DOWN   | Next menu       |
| OK     | Enter / Execute |
| BACK   | Previous level  |

---

## 🔌 Trigger Mode

```cpp
int MenuCreator::IP_MODE = LOW;
```

### Options

```cpp
LOW
HIGH
```

Use:

- `LOW` → For pull-up buttons (recommended)
- `HIGH` → For normal trigger buttons

---

## 📏 LCD Size

```cpp
short MenuCreator::COL = 16;
short MenuCreator::ROW = 2;
```

Examples:

```cpp
16x2
20x4
16x4
```

---

## ⏱ Timeout

```cpp
unsigned long MenuCreator::timeout = 60;
```

If no button pressed for 60 seconds, screen returns to idle mode.

---

## 💤 Idle Screen Messages

```cpp
MenuCreator::setIdealText(0, "Welcome");
MenuCreator::setIdealText(1, "Select Menu");
```

### Format

```cpp
setIdealText(lineNumber, "message");
```

Example:

```cpp
setIdealText(0, "My Device");
setIdealText(1, "Ready");
```

---

## 📂 Create Menus

```cpp
MenuCreator root;
MenuCreator settings;
MenuCreator info;
MenuCreator wifi;
```

---

## 🌳 Create Tree Structure

```cpp
root.appendChild(&settings);
root.appendChild(&info);

settings.appendChild(&wifi);
```

---

## 🏷 Set Menu Text

```cpp
settings << "Settings";
info << "Info";
wifi << "WiFi Setup";
```

---

## ⚡ Attach Callback

```cpp
info.attachCallBack(myFunction);
```

When selected, function runs.

Example:

```cpp
void myFunction()
{
   Serial.println("Pressed");
}
```

---

## 🔄 Main Loop

```cpp
void loop()
{
   MenuCreator::butProcess();
}
```

Must call continuously.

---

# 📋 Available Functions

| Function           | Description                |
| ------------------ | -------------------------- |
| `init()`           | Initialize LCD and buttons |
| `setRoot()`        | Set first menu             |
| `appendChild()`    | Add submenu                |
| `attachCallBack()` | Attach function            |
| `setIdealText()`   | Set idle message           |
| `butProcess()`     | Process buttons            |
| `<<`               | Set menu text              |

---

# 🎮 Navigation Example

```txt
UP      -> Previous item
DOWN    -> Next item
OK      -> Enter / Run
BACK    -> Go back
```

---

# 📜 License

This software is licensed under the **GNU GPL v3** for open-source use.

Any use of this software in closed-source or proprietary applications requires a separate commercial license from the author.

To obtain a commercial license, please contact:

**[scicopath01@gmail.com](mailto:scicopath01@gmail.com)**

---

# 👨‍💻 Author

Jayasankar JP

---

# ⭐ Support

If you like this project:

- Star repository
- Share with Arduino developers
- Improve library
- Submit pull requests
