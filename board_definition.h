#ifndef PATHFINDER_ARDUINO_BOARD_DEFINITION_H
#define PATHFINDER_ARDUINO_BOARD_DEFINITION_H

#include <Wire.h>
#include <Arduino.h>
#include <stdio.h>
#include <LiquidCrystal.h>
#include "linkedList.h"

//LCD screen parameters
#define LCD_WIDTH    16
#define LCD_HEIGHT   2

//pin definitions
#define PIN_RS       8
#define PIN_EN       9
#define PIN_D4       4
#define PIN_D5       5
#define PIN_D6       6
#define PIN_D7       7

//button pin
#define BUTTON_PIN   A0

#define EXIT_OK      0
#define EXIT_FAIL    1


//button operations ENUM
enum buttonOps {NONE, RIGHT, LEFT, UP, DOWN, SELECT};

//LCD screen initialization function
LiquidCrystal *InitializeLCD(int pin_rs, int pin_en, int pin_d4, int pin_d5, 
                             int pin_d6, int pin_d7, int lcd_width, int lcd_height);

//display menu on LCD function
int menu(LiquidCrystal *lcd);

//handling a single digit input by the user (for an x or y coordinate)
int numberHandling(LiquidCrystal *lcd);

//checks what button is being pressed
void Check(LiquidCrystal *lcd);

//handles insertion of the coordinates
int insertCoordHandle(LiquidCrystal *lcd);




#endif 
