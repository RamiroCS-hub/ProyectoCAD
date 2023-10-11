#ifndef LCD_H
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

// FUNCION PARA IMPRIMIR MENSAJES
void lcdWrite(String msg, LiquidCrystal_I2C lcd){
    //int size = sizeof(msg)/sizeof(msg[0]);
    bool contr = true;
    int size = msg.length();
    lcd.setCursor(0,0);

    if(size > 16){
        for(int i = 0; i < size; i++){
            if(i >= 16 && contr){
                lcd.setCursor(0,1);
                contr = false;
            }
            lcd.write(msg[i]);
        }  
    }else{
        lcd.print(msg);
    }
}
// FUNCION PARA IMPRIMIR MENSAJES EN OTROS COLUMNAS Y FILAS
void lcdWrite(String msg, LiquidCrystal_I2C lcd, int column, int row){
    Serial.println(msg);
    lcd.setCursor(1, 1);
    lcd.print(msg);
}
#endif //LCD_H