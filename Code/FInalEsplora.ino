#include <Esplora.h>
#include<SoftwareSerial.h>
#define RX 11 
#define TX 3
SoftwareSerial BlueT(RX,TX);
char recvChar;

void setup(){
  Serial.begin(38400);
  BlueT.begin(38400);}

void loop(){
  //Joystick
  int D=Esplora.readSlider();
  int X=Esplora.readJoystickX();
  int Y=Esplora.readJoystickY();
  if(0<=D and D<=511){
    if(-512<=Y and Y<=-100){
      if(-100<=X and X<=100){BlueT.println("C");Serial.println("C");}
    }
    else if(-100<=Y and Y<=100){
      if(-512<=X and X<=-100){BlueT.println("A");Serial.println("A");}
      else if(-100<=X and X<=100){BlueT.println("G");Serial.println("G");}
      else {BlueT.println("B");Serial.println("B");}
    }
    else {
      if(-100<=X and X<=+100){BlueT.println("D");Serial.println("D");}
    }
  }
  
  else {
    if(-512<=Y and Y<=-100){
      if(-100<=X and X<=100){BlueT.println("E");Serial.println("E");}
    }
    else if(-100<=Y and Y<=100){
      if(-512<=X and X<=-100){BlueT.println("B");Serial.println("B");}
      else if(-100<=X and X<=100){BlueT.println("G");Serial.println("G");}
      else {BlueT.println("A");Serial.println("A");}
    }
    else {
      if(-100<=X and X<=+100){BlueT.println("F");Serial.println("F");}
    }
  }
}
