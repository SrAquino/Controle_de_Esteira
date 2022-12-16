#include <HCSR04.h>   //Biblioteca para usar o sensor ultrasônico
#include <Stepper.h>  //Biblioteca para controlar o motor de passos

//Pinos para o sensor ultrasônico
const byte triggerPin = 8;    //Trigger
const byte echoPin = 9;       //Echo
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

//Pinos para controlar o motor
const int stepsPerRevolution = 500; 
Stepper motor(stepsPerRevolution, 10,11,12,13); 

#define led1 2  //Led Verde
#define led2 3  //Led Amarelo
#define led3 4  //Led Azul

int cont = 0;   //Contador de itens

void setup() {
  Serial.begin(9600);

//Define os pinos dos leds
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

//Determina a velocidade inicial do motor 
 motor.setSpeed(60);
}

void loop() {
  float distance = distanceSensor.measureDistanceCm();

//Gira o motor no sentido horario
  motor.step(50);


//Serial.println(distance);
  delay(500);
  Serial.println(distance);

    if(distance < 5){
      
      cont++;
      Serial.println(cont);

      if(cont == 1){
        digitalWrite(led1,HIGH);
      }

      if(cont == 2 ){
        digitalWrite(led2,HIGH);
      }

      if(cont == 3){
        digitalWrite(led3,HIGH);
      }

      if(cont > 3){
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        digitalWrite(led3,LOW);
        delay(10000);
        cont = 0;
      }

      while(distance < 8){
        distance = distanceSensor.measureDistanceCm();
        //Serial.println(distance);
        motor.step(40);
        delay(500);
      }
    }

}
