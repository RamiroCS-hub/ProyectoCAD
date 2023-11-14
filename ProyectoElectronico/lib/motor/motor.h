#ifndef MOTOR_H
#define MOTOR_H
#define WAIT 20
#define SERVO 21
#define DIREC 27
#define MOTOR 26
#include "Arduino.h"
#include <ESP32Servo.h>

void stepMotor(void);
//Función para 2 actuadores
int moveMotor(int posAIr, int posActual, int pinAct1, int pinAct2, int time) { 
    Serial.print("Posición a ir: "); //Posición a la que se quiere mover
    Serial.println(posAIr);
    Serial.print("Pin act1: "); //Pin del actuador que se va a activar primero
    Serial.println(pinAct1);
    Serial.print("Pin act2: "); //Pin del actuador que se va a activar segundo
    Serial.println(pinAct2);
    Serial.print("El Tiempo de espera es: ");
    Serial.println(time);
    // Mover el motor paso a paso con el driver hasta que se llega a la posición que se requiera 
    if(posAIr > posActual){ 
        while(posAIr != posActual) {
            digitalWrite(DIREC, HIGH);
            stepMotor();
            posActual += 1;
        };
    }else{
        while(posAIr != posActual) {
            digitalWrite(DIREC, LOW);
            stepMotor();
            posActual -= 1;
        };
    }
    //Activación de los actuadores - Orden 1°Bomba - 2°Electrovalvula
    digitalWrite(pinAct1, HIGH);
    Serial.println("Actuador 1");
    delay(1000);
    digitalWrite(pinAct2, HIGH);
    Serial.println("Actuador 2");
    delay(time);
    digitalWrite(pinAct1,LOW);
    digitalWrite(pinAct2, LOW);
    delay(1000);
    return posActual;
};

//Función para 1 actuador
int moveMotor(int posAIr, int posActual, int pinAct, int size, Servo servoMotor){
    pinMode(MOTOR, OUTPUT);
    
    Serial.println(posAIr);
    Serial.println(pinAct);

    //Se mueve el motor hasta la posición que se requiere
    if(posAIr > posActual){
        while(posAIr != posActual) {
            digitalWrite(DIREC, HIGH);
            stepMotor();
            posActual += 1;
        };
    }else{
        while(posAIr != posActual) {
            digitalWrite(DIREC, LOW);
            stepMotor();
            posActual -= 1;
        };
    }
    
    for(int i = 0; i < size; i++){
        delay(800);
        servoMotor.write(0);
        delay(800);
        servoMotor.write(180);
    }
    return posActual;
};

//Vuelve el motor a la posición inicial - Siempre que se termina un pedido se vuelve a la posición inicial
void backMotor (int posAct){
    pinMode(MOTOR, OUTPUT);
    while(posAct != 0){
        digitalWrite(DIREC, LOW);
        stepMotor();
        posAct-=1;
    }
    Serial.println("Volviendo atras el motor...");
    
    delay(2000);
};

void stepMotor(){
    for(int i = 0; i<200; i++){
        digitalWrite(MOTOR, HIGH);
        delay(2);
        digitalWrite(MOTOR, LOW);
        delay(2);
    }   
}

#endif // MOTOR_H
