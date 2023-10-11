#ifndef MOTOR_H
#define MOTOR_H
#define DIREC 2
#define WAIT 20
#define PINMOTOR 23
#define SERVO 21
#include "Arduino.h"
#include <ESP32Servo.h>

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
            digitalWrite(PINMOTOR, HIGH);
            posActual += 1;
            delay(2);
            digitalWrite(PINMOTOR, LOW);
            delay(2);
        };
    }else{
        while(posAIr != posActual) {
            digitalWrite(DIREC, LOW);
            digitalWrite(PINMOTOR, HIGH);
            posActual -= 1;
            delay(2);
            digitalWrite(PINMOTOR, LOW);
            delay(2);
        };
    }
    //Activación de los actuadores - Orden 1°Bomba - 2°Electrovalvula
    digitalWrite(pinAct1, HIGH);
    delay(20);
    digitalWrite(pinAct2, HIGH);
    Serial.println("Actuadores prendidos");
    delay(time);
    digitalWrite(pinAct1,LOW);
    digitalWrite(pinAct2, LOW);
    delay(3000);
    return posActual;
};

//Función para 1 actuador
int moveMotor(int posAIr, int posActual, int pinAct, int size){
    Servo servoMotor; //Se crea un objeto para controlar el servo
    Serial.println(posAIr);
    Serial.println(pinAct);
    servoMotor.attach(SERVO); //Se vincula el pin del servo al objeto
    //Se mueve el motor hasta la posición que se requiere
    if(posAIr > posActual){
        while(posAIr != posActual) {
            digitalWrite(DIREC, HIGH);
            digitalWrite(PINMOTOR, HIGH);
            posActual += 1;
            delay(2);
            digitalWrite(PINMOTOR, LOW);
            delay(2);
        };
    }else{
        while(posAIr != posActual) {
            digitalWrite(DIREC, LOW);
            digitalWrite(PINMOTOR, HIGH);
            posActual -= 1;
            delay(2);
            digitalWrite(PINMOTOR, LOW);
            delay(2);
        };
    }
    for(int i = 0; i <= size; i++){
        servoMotor.write(90);
    }
    delay(3000);
    return posActual;
};
//Vuelve el motor a la posición inicial - Siempre que se termina un pedido se vuelve a la posición inicial
void backMotor (int posAct){
    while(posAct != 0){
        digitalWrite(DIREC, LOW);
        posAct -= 1;
        digitalWrite(PINMOTOR, HIGH);
        delay(2);
        digitalWrite(PINMOTOR, LOW);
        delay(2);
    }
    Serial.println("Volviendo atras el motor...");
    
    delay(2000);
};

#endif // MOTOR_H
