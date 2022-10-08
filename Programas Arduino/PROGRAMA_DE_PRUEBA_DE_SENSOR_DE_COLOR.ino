// presionar el boton para obtener datos de lectura 
#include <ColorPAL.h>

ColorPAL sensor;
const int pulsador = 11;
const int ledrojo = 2;
const int ledazul = 3;
const int ledblanco =4;
int boton;
void setup()
{
  sensor.attachPAL(12);
  Serial.begin(9600);
  pinMode(pulsador, INPUT);
  pinMode (ledrojo, OUTPUT);
  pinMode (ledazul, OUTPUT);
  pinMode (ledblanco, OUTPUT);
}

void loop()
{
  int red = sensor.redPAL();
  int green = sensor.greenPAL();
  int blue = sensor.bluePAL();
  boton=digitalRead(pulsador);

delay(100);
      if (boton == HIGH) {
        Serial.print("red: ");
        Serial.print(red);
        Serial.print("    ");
        Serial.print("green: ");
        Serial.print(green);
        Serial.print("    ");
        Serial.print("blue: ");
        Serial.println(blue);
        
      if (red/2 > blue && red/2 > green) {
      Serial.println("rojo");
      digitalWrite(ledrojo, HIGH);
      delay(500);
      digitalWrite(ledrojo, LOW);
    } else if (blue/2 > green && blue/2 > red) {
        Serial.println("azul");
        digitalWrite(ledazul, HIGH);
        delay(500);
        digitalWrite(ledazul, LOW);
    } else {
      Serial.println("no color");
      digitalWrite(ledblanco, HIGH);
      delay(500);
      digitalWrite(ledblanco, LOW);
    }
    }
}
