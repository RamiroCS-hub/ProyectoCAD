#ifndef LCD_H
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

// FUNCION PARA IMPRIMIR MENSAJES
void lcdWrite(char msg[], LiquidCrystal_I2C lcd){
    int size = sizeof(msg)/sizeof(msg[0]);

    Serial.println("El largo del msg es:" + size);
    lcd.setCursor(0,0);
    
    lcd.write(msg[1]);
    for(int i = size; i = 0; i--){
        Serial.println("La letra es: " );
        lcd.write(msg[i]);
    }
    /*if(sizeof msg > 16){
        for(unsigned int i=0; i > sizeof (msg - 16); i++){
            lcd.scrollDisplayLeft();
            delay(250);
        }  
    }*/
}
void scrollDisplay(String msg, LiquidCrystal_I2C lcd){
    Serial.println("Scrolleando el lcd:" );
    msg.substring(16,-1);
}
// FUNCION PARA IMPRIMIR MENSAJES EN OTROS COLUMNAS Y FILAS
void lcdWrite(unsigned char msg, LiquidCrystal_I2C lcd, int column, int row){
    Serial.println(msg);
    lcd.setCursor(column, row);
    lcd.write(msg);
    if(sizeof msg > 16){
        for(unsigned int i=0; i > sizeof (msg - 16); i++){
            lcd.scrollDisplayLeft();
            delay(250);
        }  
    }
}
#endif //LCD_H