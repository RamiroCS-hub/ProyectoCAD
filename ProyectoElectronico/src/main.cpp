#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Keypad.h>
#include <motor.h>
#include <LiquidCrystal_I2C.h>
#include <lcd.h>

/* <---------NUCLEO 1 --------> */
// Definir pines de parte de celdas peltier
#define SEN_F 13
#define SEN_C 12
#define COOLLER_C 0
#define COOLLER_F 00
#define RESIS 000 
#define PELT_ 0000

//Selecciona el pin al que se conecta el sensor de temperatura
const int sen_peltf = SEN_F;
const int sen_peltc = SEN_C;
// Umbrales de temperatura
const int umb_c = 80;
const int umb_f = 3;

//Crea la tarea
TaskHandle_t Task1;

// //Comunicar que vamos a utilizar la interfaz oneWire
// OneWire senPeltf(sen_peltf);
// OneWire senPetc(sen_peltc);

// //Indica que el sensor utilizará la interfaz OneWire
// DallasTemperature sensor1(&senPeltf);
// DallasTemperature sensor2(&senPeltc);

void loop1(void *parameter){
   while(1){
      //Leer la temperatura
      Serial.println("Segundo núcleo");
      digitalWrite(22,HIGH);
      delay(1000);
      digitalWrite(22,LOW);
      delay(1000);
      // Serial.print("Mandando comandos a los sensores ");
      // sensor1.requestTemperatures();
      // sensor2.requestTemperatures();
     
      // //Lectura en grados celsius del contenedor de Leche
      // float tempF = sensor1.getTempCByIndex(0);
      // //Declaro el puntero que va a tener la temperatura y lo apunto a donde se guarda la temp de la Peltier Fría
      // float *p_temp = &tempF;

      // //Escribir los datos en el monitor de serie
      // Serial.print("Temperatura sensor frío : ");
      // Serial.print(*p_temp);
      // Serial.println("°C");

      // //Prender la celda peltier hasta que se nivele la temperatura
      // while(*p_temp > umb_f){
      //    digitalWrite(PELT_F, HIGH);
      //    digitalWrite(COOLLER_F, HIGH);
      //    *p_temp = sensor1.getTempCByIndex(0);
      // };

      // //Apagar el sistema de refrigeración
      // digitalWrite(COOLLER_F, LOW);
      // digitalWrite(PELT_F, LOW);

      // //Lectura en grados celcius del contenedor de cafe
      // float tempC = sensor2.getTempCByIndex(0);
      // //Apunto al puntero donde esta la temperatura caliente
      // p_temp = &tempC;

      // //Prender la celda peltier hasta que se nivele la temperatura
      // while(*p_temp < umb_c){
      //    digitalWrite(PELT_C, HIGH);
      //    digitalWrite(COOLLER_C, HIGH);
      //    *p_temp = sensor2.getTempCByIndex(0);
      // }

      // //Escribir los datos en el monitor de serie
      // Serial.print("Temperatura sensor caliente : ");
      // Serial.print(*p_temp);
      // Serial.println("°C");

      // //Apagar el sistemas de calefacción
      // digitalWrite(COOLLER_C, LOW);
      // digitalWrite(PELT_C, LOW);

      // // Lectura de la temperatura cada 5 segundos
      // delay(5000);
   }
  vTaskDelay(10);
} 

//Creo un objeto de la libreria liquidCrystal_I2C para controlar el LCD
LiquidCrystal_I2C lcd(0x3F, 16, 2); //Lo guardo en la dirección 0x3F, 16 columnas 2 filas
/* -------- NUCLEO 0 --------- */
#define CAFE '1'
#define LECHE '2'
#define CEREALES '4'
#define CAFECLECHE '5'
#define CEREALESCLECHE '7'
#define CHICO '3'
#define MEDIANO '6'
#define GRANDE '9'
#define TIMEC 2000
#define TIMEM 20
#define TIMEG 30
#define LOOPC 2
#define LOOPM 4
#define LOOPG 6

// //Pines de cafe
#define POSCAFE 120
const int bomCafe = 22;
const int elecCafe = 23;
// //Pines de leche
// const int posLeche = 16;
// const int bomLeche = 35;
// const int elecLeche = 33;
// //Pines de cereales
const int posCere = 70;
const int servo = 27;

//Definición de teclado matricial
const uint8_t ROWS = 4;
const uint8_t COLS = 4;

//Definición de la matriz
char keys[ROWS][COLS] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};

//Declaraciones de pines de la matriz
byte rowPins[ROWS] = { 17, 5, 18, 19 };
byte columnPins[COLS] = { 15, 2, 4, 16 };

Keypad keypad = Keypad( makeKeymap(keys), rowPins, columnPins, ROWS, COLS );

void setup() {
   Serial.begin(9600);
   /*//Loop 1
   lcd.init();
   //Prendo la luz de fondo
   lcd.backlight();
   lcd.setCursor(0,1);*/

   pinMode(elecCafe, OUTPUT);
   pinMode(bomCafe, OUTPUT);
   //Loop 2
   xTaskCreatePinnedToCore(
       loop1,
       "Task1",
       1000, //Tamaño de la pila
       NULL,
       1,
       &Task1, //Referencio la tarea que había creado antes
      0); //Número de núcleo
  //sensor1.begin();
  //sensor2.begin();
}

/* <--------- NUCLEO 0 ---------> */

void loop() {
   int posAct = 0;
   int waitTime = 0; //Tiempo que va a estar quieto el vaso
   int loopServo = 0; //Cantidad de pasos del servo
   bool contr = 1;
   char key;
   char size;

   //INGRESO DE TAMAÑO DEL DESAYUNO
   //lcdWrite((unsigned char) * ("Ingrese el tamaño:"), lcd);
   do{
      size = keypad.getKey();
      if(size){
         Serial.println(size);
         contr = 0;
         //lcd.clear();
      }
      delay(100);
   } while(contr);
   Serial.println(size);
   
   /* Se cambian las variables de tiempo y mov. del servo dependiendo del tamaño de desayuno
      que se pidió */
   switch(size) {
      default:
         waitTime = TIMEC;
         loopServo = LOOPC;
         //lcdWrite((unsigned char)* ("Tamaño Chico"), lcd);
         Serial.println("Tamaño chico");
         break;
      case CHICO:
         waitTime = TIMEC;
         loopServo = LOOPC;
         //lcdWrite((unsigned char)* ("Tamaño Chico"), lcd);
         Serial.println("Tamaño chico");
         break;
      case MEDIANO:
         waitTime = TIMEM;
         loopServo = LOOPM;
         //lcd.setCursor(0, 1);
         //lcdWrite((unsigned char)* ("Tamaño Mediano"), lcd);
         break;
      case GRANDE:
         waitTime = TIMEG;
         loopServo = LOOPG;
         //lcd.setCursor(0, 1);
         //lcdWrite((unsigned char)* ("Tamaño Grande"), lcd);
         break;
   };

   /* INGRESO DE QUE SE QUIERE PREPARAR */
   //lcd.clear();
   //lcdWrite((unsigned char)* ("Ingrese lo que quiere preparar"), lcd);  
   contr = 1;
   do {
      key = keypad.getKey();
      if(key){
         Serial.println(key);
         contr = 0;
      }
      delay(50);
   } while(contr);

   //lcd.clear();

   // Dependiendo de que se ingresa se llama a la función con la posición a la que se quiere mover
   switch(key){
      default:
         //lcdWrite((unsigned char)* ("Elija algo del menú"), lcd);
         Serial.println("Elija algo del menú");
         break;
      case CAFE:
         // lcdWrite((unsigned char)* ("Elijió Cafe"), lcd);
         // lcdWrite((unsigned char)* ("Preparando..."), lcd, 1, 0);
         Serial.println("Elijió el café");
         posAct = moveMotor(POSCAFE, posAct, bomCafe, elecCafe, waitTime);
         Serial.print("La posición del vaso es: ");
         Serial.println(posAct);
         // lcd.clear();
         // lcdWrite((unsigned char)* ("MUCHAS GRACIAS!"), lcd);
         break;
      // case LECHE:
      //    lcdWrite((unsigned char)* ("Elijió Leche"), lcd);
      //    lcd.clear();
      //    lcdWrite((unsigned char)* ("Preparando..."),lcd);
      //    posAct = moveMotor(posLeche, posAct, bomLeche, elecLeche, waitTime);
      //    lcd.clear();
      //    lcdWrite((unsigned char)* ("MUCHAS GRACIAS!"), lcd);
      //    break;
      case CEREALES:
         /*lcdWrite((unsigned char)* ("Elijió los cereales"), lcd);
         lcd.clear();
         lcdWrite((unsigned char)* ("Preparando..."), lcd);*/
         Serial.println("Tirando Cereales");
         posAct = moveMotor(posCere, posAct, servo, loopServo);
         //lcd.clear();
         //lcdWrite((unsigned char)* ("MUCHAS GRACIAS!"), lcd);
         break;
      // case CAFECLECHE:
      //    lcdWrite((unsigned char)* ("Elijió el cafe con leche"), lcd);
      //    lcd.clear();
      //    lcdWrite((unsigned char)* ("Preparando..."), lcd);
      //    posAct = moveMotor(posCafe, posAct, bomCafe, elecCafe, waitTime);
      //    posAct = moveMotor(posLeche, posAct, bomLeche, elecLeche, waitTime);
      //    lcd.clear();
      //    lcdWrite((unsigned char)* ("MUCHAS GRACIAS!"), lcd);
      //    break;
      // case CEREALESCLECHE:
      //    lcdWrite((unsigned char)* ("Elijió los cereales con leche"), lcd);
      //    lcd.clear();
      //    lcdWrite((unsigned char)* ("Preparando..."), lcd);
      //    // posAct = moveMotor(posCere, posAct, servo, loopServo);
      //    posAct = moveMotor(posLeche, posAct, bomLeche, elecLeche, waitTime);
      //    lcd.clear();
      //    lcdWrite((unsigned char)* ("MUCHAS GRACIAS!"), lcd);
      //    break;
   };
   
   //Vuelve el motor a la posición inicial
   backMotor(posAct);  
}  


