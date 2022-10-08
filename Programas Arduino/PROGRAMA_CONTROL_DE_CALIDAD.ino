#include <ColorPAL.h>
#include "HX711.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int Trigger = 8;
const int Echo = 9;
const int pulsador = 11;
const int rojo = 2;
const int azul = 3;
const int no_color =4;
const int peso_si =5;
const int peso_no =6;
const int DOUT=A1;
const int CLK=A0;
const int led_rojo =13;
const int led_azul =10;
const int led_no_color =7;
const int led_peso_si =A2;
const int led_peso_no =A3;
int boton;
int espera = 5000;
float pmax =0.35;
float pmin =0.2;
int red;
int green;
int blue;
int i;

ColorPAL sensor;
HX711 balanza;
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {

  Serial.begin(9600);

  balanza.begin(DOUT, CLK);
  sensor.attachPAL(12);
  lcd.init();
  lcd.backlight();  

  lcd.print("iniciando");
  Serial.print("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(407295);
  balanza.tare(20);
  Serial.println("Listo para pesar");
  lcd.clear();

  pinMode (Trigger, OUTPUT);
  pinMode (Echo, INPUT);
  pinMode (pulsador, INPUT);
  pinMode (rojo, OUTPUT);
  pinMode (azul, OUTPUT);
  pinMode (no_color, OUTPUT);
  pinMode (peso_si, OUTPUT);
  pinMode (peso_no, OUTPUT);
  pinMode (led_rojo, OUTPUT);
  pinMode (led_azul, OUTPUT);
  pinMode (led_no_color, OUTPUT);
  pinMode (led_peso_si, OUTPUT);
  pinMode (led_peso_no, OUTPUT);

  digitalWrite(Trigger, LOW); 
  digitalWrite(rojo, LOW);
  digitalWrite(azul, LOW);
  digitalWrite(no_color, LOW);
  digitalWrite(peso_si, LOW);
  digitalWrite(peso_no, LOW);
  digitalWrite(led_rojo, LOW);
  digitalWrite(led_azul, LOW);
  digitalWrite(led_no_color, LOW);
  digitalWrite(led_peso_si, LOW);
  digitalWrite(led_peso_no, LOW);

}

void loop() {

  boton=digitalRead(pulsador);
  float peso;
  long t;
  long d;
  
  lcd.print("esperando...");

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH);
  d = t/59;
  
  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.print("cm");
  Serial.println();

  delay(100);
  
  lcd.clear();

  if (d < 4 || boton == HIGH) {
    
    i=0;

    while (i < 6) {
      red = sensor.redPAL();
      green = sensor.greenPAL();
      blue = sensor.bluePAL();
      Serial.println(i);
      Serial.print("red: ");
      Serial.print(red);
      Serial.print("    ");
      Serial.print("green: ");
      Serial.print(green);
      Serial.print("    ");
      Serial.print("blue: ");
      Serial.println(blue);
      delay(500);
      i=i+1;
    }
      
    Serial.print("Peso: ");
    Serial.print(balanza.get_units(20),3);
    Serial.println(" kg");
    peso=balanza.get_units(20); 
    
      if (red/2 > blue && red/2 > green && peso <= pmax && peso >= pmin) {
         Serial.println("rojo");
         Serial.println("peso aceptado");
         Serial.println();
         digitalWrite(rojo, HIGH);
         digitalWrite(peso_si, HIGH);
         digitalWrite(led_rojo, HIGH);
         digitalWrite(led_peso_si, HIGH);
         lcd.print("color: rojo");
         lcd.setCursor(0, 1);
         lcd.print("peso: ");
         lcd. print(peso);
         lcd.print("Kg");
         delay(espera);
         digitalWrite(rojo, LOW);
         digitalWrite(peso_si, LOW);
         digitalWrite(led_rojo, LOW);
         digitalWrite(led_peso_si, LOW);
         lcd.clear();
      } 
      
      else if (red/2 > blue && red/2 > green && peso < pmin) {
         Serial.println("rojo");
         Serial.println("peso rechazado");
         Serial.println();
         lcd.print("color: rojo");
         lcd.setCursor(0, 1);
         lcd.print("peso: ");
         lcd. print(peso);
         lcd.print("Kg");
         digitalWrite(rojo, HIGH);
         digitalWrite(peso_no, HIGH);
         digitalWrite(led_rojo, HIGH);
         digitalWrite(led_peso_no, HIGH);
         delay(espera);
         digitalWrite(rojo, LOW);
         digitalWrite(peso_no, LOW);
         digitalWrite(led_rojo, LOW);
         digitalWrite(led_peso_no, LOW);
         lcd.clear();
      }
      
      else if (red/2 > blue && red/2 > green && peso > pmax) {
         Serial.println("rojo");
         Serial.println("peso rechazado");
         Serial.println();
         lcd.print("color: rojo");
         lcd.setCursor(0, 1);
         lcd.print("peso: ");
         lcd. print(peso);
         lcd.print("Kg");
         digitalWrite(rojo, HIGH);
         digitalWrite(peso_no, HIGH);
         digitalWrite(led_rojo, HIGH);
         digitalWrite(led_peso_no, HIGH);
         delay(espera);
         digitalWrite(rojo, LOW);
         digitalWrite(peso_no, LOW);
         digitalWrite(led_rojo, LOW);
         digitalWrite(led_peso_no, LOW);
         lcd.clear();
      }

      else if (blue/2 > green && blue/2 > red && peso <= pmax && peso >= pmin) {
         Serial.println("azul");
         Serial.println("peso aceptado");
         Serial.println();
         lcd.print("color: azul");
         lcd.setCursor(0, 1);
         lcd.print("peso: ");
         lcd. print(peso);
         lcd.print("Kg");
         digitalWrite(azul, HIGH);
         digitalWrite(peso_si,HIGH);
         digitalWrite(led_azul, HIGH);
         digitalWrite(led_peso_si, HIGH);
         delay(espera);
         digitalWrite(azul, LOW);
         digitalWrite(peso_si, LOW);
         digitalWrite(led_azul, LOW);
         digitalWrite(led_peso_si, LOW);
         lcd.clear();
      }
      
      else if (blue/2 > green && blue/2 > red && peso < pmin) {
         Serial.println("azul");
         Serial.println("peso rechazado");
         Serial.println();
         lcd.print("color: azul");
         lcd.setCursor(0, 1);
         lcd.print("peso: ");
         lcd. print(peso);
         lcd.print("Kg");
         digitalWrite(azul, HIGH);
         digitalWrite(peso_no,HIGH);
         digitalWrite(led_azul, HIGH);
         digitalWrite(led_peso_no, HIGH);
         delay(espera);
         digitalWrite(azul, LOW);
         digitalWrite(peso_no, LOW);
         digitalWrite(led_azul, LOW);
         digitalWrite(led_peso_no, LOW);
         lcd.clear();
      }
      
      else if (blue/2 > green && blue/2 > red && peso > pmax) {
         Serial.println("azul");
         Serial.println("peso rechazado");
         Serial.println();
         lcd.print("color: azul");
         lcd.setCursor(0, 1);
         lcd.print("peso: ");
         lcd. print(peso);
         lcd.print("Kg");
         digitalWrite(azul, HIGH);
         digitalWrite(peso_no, HIGH);
         digitalWrite(led_azul, HIGH);
         digitalWrite(led_peso_no, HIGH); 
         delay(espera);
         digitalWrite(azul, LOW);
         digitalWrite(peso_no, LOW);
         digitalWrite(led_azul, LOW);
         digitalWrite(led_peso_no, LOW);
         lcd.clear();
      }

      else if (peso <= pmax && peso >= pmin) {
        Serial.println("no color");
        Serial.println("peso aceptado");
        Serial.println();
        lcd.print("color: no color");
        lcd.setCursor(0, 1);
        lcd.print("peso: ");
        lcd. print(peso);
        lcd.print("Kg");
        digitalWrite(no_color, HIGH);
        digitalWrite(peso_si, HIGH);
        digitalWrite(led_no_color, HIGH);
        digitalWrite(led_peso_si, HIGH);
        delay(espera);
        digitalWrite(no_color, LOW);
        digitalWrite(peso_si, LOW);
        digitalWrite(led_no_color, LOW);
        digitalWrite(led_peso_si, LOW);
        lcd.clear();
      }
      
      else {
        Serial.println("no color");
        Serial.println("peso rechazado");
        Serial.println();
        lcd.print("color: no color");
        lcd.setCursor(0, 1);
        lcd.print("peso: ");
        lcd. print(peso);
        lcd.print("Kg");
        digitalWrite(no_color, HIGH);
        digitalWrite(peso_no, HIGH);
        digitalWrite(led_no_color, HIGH);
        digitalWrite(led_peso_no, HIGH);
        delay(espera);
        digitalWrite(no_color, LOW);
        digitalWrite(peso_no, LOW);
        digitalWrite(led_no_color, LOW);
        digitalWrite(led_peso_no, LOW);
        lcd.clear();
      }
  }   
} 
