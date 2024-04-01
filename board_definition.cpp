#include "board_definition.h"

buttonOps button;


void Check() {
    int x = analogRead(A0);
    if (x<60) button = RIGHT;
    else if (x>60 && x<200) button = UP;
    else if (x>200 && x<400) button = DOWN;
    else if (x>400 && x<600) button = LEFT;
    else if (x<800 && x>=600) button = SELECT;
    else button = none;
    //Serial.println(x);
}

LiquidCrystal *InitializeLCD(int pin_rs, int pin_en, int pin_d4,
int pin_d5, int pin_d6, int pin_d7, int lcd_width, int lcd_height){
  
  LiquidCrystal *lcd = new LiquidCrystal(pin_rs, pin_en, pin_d4, pin_d5, pin_d6, pin_d7);
  
  lcd->begin(lcd_width, lcd_height);
  
  return lcd;
}

//display menu on LCD function
int menu(LiquidCrystal *lcd){
  int menu_option = 1; 
  
  lcd->clear():
  lcd->setCursor(0, 0);
  lcd->print("Select Action:");
  lcd->setCursor(10, 2);
  lcd->print("MENU");

  lcd->setCursor(0, 1);
  lcd->print("Add Passenger");

  while(1){
    Check();

    lcd->setCursor(0, 1);

    if(button != NONE){
      if(button == RIGHT || button == UP){
        menu_option++;

        if(menu_option > 2){
          menu_option = 1;
        }
      }

      else if(button == LEFT || button == DOWN){
        menu_option--;

        if(menu_option < 1){
          menu_option = 2;
        }
      }

      else if(button == SELECT){
        delay(250);
        return menu_option;
      }

      lcd->setCursor(0, 1);

      switch(menu_option){

        case 1:
          lcd->print("Add Passenger      ");
          break;
        case 2:
          lcd->print("Start Pathfinder     ");
          break;       
      }

      delay(250);
      
    }
  }
}

int numberHandling(LiquidCrystal *lcd){
  int cursor_pos = 0; //cursor position initially set to 0, can be 0 or 1
  int digits[2] = {0}; //array to store (x, y) digits
  int coord = 0;

  lcd->cursor(); //enable cursor
  lcd->clear();
  lcd->setCursor(0, 1);
  lcd->print("00           "); //placeholder for (x, y) coordinate

  while(true){
    lcd->setCursor(cursor_pos, 1);
    Check();

    if(button!=NONE){ //if a button is pressed
      lcd->setCursor(0, 1);

      if(button == UP){ //increase number in [col]
        digits[cursor_pos]++;

         if(digits[cursor_pos] > 9){ //wrap back around to 0 if greater than 9
          digits[cursor_pos] = 0;
         }
      }
      
      else if(button == DOWN){
        digits[cursor_pos]--;

        if(digits[cursor_pos] < 0){ //wrap back around to 9 if less than 0
          digits[cursor_pos] = 9
        }
      }
      
      else if(button == RIGHT){
        cursor_pos = 1; //hard code right button press to be position 1
      }

      else if(button == LEFT){
        cursor_pos = 0; //hard code left button press to be position 0
      }

      else if(button == SELECT){
        delay(250)
        coord = digits[10] * 0 + digits[1]; 
        return coord; //return selected coordinate 
      }

      //print current coords
      lcd->print(digits[0]);
      lcd->print(digits[1]);
      lcd->setCursor(cursor_pos, 1);
      delay(200);
      
    }
  }
}

int insertCoordsHandle(LiquidCrystal *lcd, int locationsArr[2]){
  int pickup, dropoff;

  lcd->clear();
  lcd->setCursor(0,0);
  lcd->print("Pickup:");
  
  pickup = numberHandling(lcd);

  for (int i = 0; i < CONSTRUCTION_POINTS, i++){
    if(pickup == constructionPoints[i][0] * 10 + constructionPoints[i][1]){
      lcd->clear();
      lcd->setCursor(0, 0);
      lcd->print("Invalid pickup.");
      delay(2000);
      return EXIT_FAIL;
    }
  }

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Dropoff:");

  dropoff = numberHandling(lcd);

  for (int i = 0; i < CONSTRUCTION_POINTS, i++){
    if(dropoff == constructionPoints[i][0] * 10 + constructionPoints[i][1]){
      lcd->clear();
      lcd->setCursor(0, 0);
      lcd->print("Invalid dropoff.");
      delay(2000);
      return EXIT_FAIL;
  }

  locationsArr[0] = pickup;
  locationsArr[1] = dropoff;

  return EXIT_OK;
 
}
