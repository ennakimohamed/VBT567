#include <SPI.h>  
#include <Pixy.h>
Pixy pixy;
//Moteurs
    //-- Back Right --
  int ENA=11; //Connecté à Arduino pin 11(sortie PWM) 
  int IN1=13; //Connecté à Arduino pin 13
  int IN2=12; //Connecté à Arduino pin 12
    //-- Back Left --
  int ENB=10; //Connecté à Arduino pin 10(Sortie PWM) 
  int IN3=7; //Connecté à Arduino pin 8
  int IN4=8; //Connecté à Arduino pin 7
    //-- Front Right --
  int ENC=9; //Connecté à Arduino pin 9(sortie PWM) 
  int IN5=5; //Connecté à Arduino pin 5
  int IN6=4; //Connecté à Arduino pin 4
    //-- Front Left --
  int END=6; //Connecté à Arduino pin 6(Sortie PWM) 
  int IN7=3; //Connecté à Arduino pin 3
  int IN8=2; //Connecté à Arduino pin 2
//Pixy
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
//Laser
  int laserPin = 53;
//Bluetouth
  char Data;
  int V0=0;
  int V1=80;
  int V2=170;
  int V3=255;
//UltraSon
  const int trig =51; //broche TRIGGER
  const int echo=49; //broche ECHO
  long measure=0;
  const long MEASURE_TIMEOUT=25000UL; //25ms = 8m à 340m/s
  const float SOUND_SPEED = 340.0 / 1000; //Vitesse du son dans l'air en mm/us
  float distance=0;



void setup(){
    Serial.begin(38400);
    // --Module bluetooth--
        Serial1.begin(38400);
    // --Voiture --
        pinMode(ENA,OUTPUT);
        pinMode(ENB,OUTPUT);
        pinMode(IN1,OUTPUT);
        pinMode(IN2,OUTPUT);
        pinMode(IN3,OUTPUT);
        pinMode(IN4,OUTPUT);
        pinMode(ENC,OUTPUT);
        pinMode(END,OUTPUT);
        pinMode(IN5,OUTPUT);
        pinMode(IN6,OUTPUT);
        pinMode(IN7,OUTPUT);
        pinMode(IN8,OUTPUT);
        digitalWrite(IN2,LOW);// Moteur A - Ne pas tourner 
        digitalWrite(IN1,HIGH);
        digitalWrite(IN4,LOW);// Moteur B - Ne pas tourner
        digitalWrite(IN3,HIGH);
        digitalWrite(IN6,LOW);// Moteur C - Ne pas tourner 
        digitalWrite(IN5,HIGH);
        digitalWrite(IN8,LOW);// Moteur D - Ne pas tourner
        digitalWrite(IN7,HIGH);
    //-- Laser --
        pinMode(laserPin, OUTPUT);
        digitalWrite(laserPin, LOW);
    //-- UltraSon --
        pinMode(trig,OUTPUT);
        digitalWrite(trig, LOW); //la broche TRIGGER doit être à LOW au repos 
        pinMode(echo,INPUT);
    //-- Pixy --
        pixy.init();
}



void loop(){
  //US
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);
  measure = pulseIn(echo, HIGH,MEASURE_TIMEOUT);
  distance = (measure/2.0)*SOUND_SPEED; // /2.0 car aller-retour
  Serial.println(distance);
  if(distance<300 and distance>10){
    analogWrite(ENA,0);
    analogWrite(ENB,0); 
    analogWrite(ENC,0);
    analogWrite(END,0);
    //Pixy
    blocks = pixy.getBlocks();
    if (blocks)
    {
      i++;
      if (i%50==0)
      {
        sprintf(buf, "Detected %d:\n", blocks);
        for (j=0; j<blocks; j++)
        {
          sprintf(buf, "  block %d: ", j);
          switch (pixy.blocks[j].signature) {
            case 1:
            for(int x=0; x<100; x++){
              digitalWrite(laserPin, HIGH);
              delay(100);
              digitalWrite(laserPin, LOW);
              delay(100);
              Serial.println(x);}
              digitalWrite(laserPin, LOW);
              break;
            case 2:
            for(int x=0; x<100; x++){
              digitalWrite(laserPin, HIGH);
              Serial.println(x);}
              digitalWrite(laserPin, LOW);
              break;}
           }
          }
         }
    digitalWrite(IN1,LOW);// Moteur A - Ne pas tourner 
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);// Moteur B - Ne pas tourner
    digitalWrite(IN4,HIGH);
    digitalWrite(IN5,LOW);// Moteur C - Ne pas tourner 
    digitalWrite(IN6,HIGH);
    digitalWrite(IN7,LOW);// Moteur D - Ne pas tourner
    digitalWrite(IN8,HIGH);
    analogWrite(ENA,V3);
    analogWrite(ENB,V3); 
    analogWrite(ENC,V3);
    analogWrite(END,V3);
    delay(2000);
    }
  else{ 
    while (Serial1.available()){
    Serial.println(Data);
    Data=Serial1.read();
    if (Data=='A'){
      //dir=1      
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      digitalWrite(IN5,LOW);
      digitalWrite(IN6,HIGH);
      digitalWrite(IN7,HIGH);
      digitalWrite(IN8,LOW);
    
      analogWrite(ENA,V3);
      analogWrite(ENB,V3); 
      analogWrite(ENC,V3);
      analogWrite(END,V3);
      }
    if (Data=='B'){      
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      digitalWrite(IN5,HIGH);
      digitalWrite(IN6,LOW);
      digitalWrite(IN7,LOW);
      digitalWrite(IN8,HIGH);

      analogWrite(ENA,V3);
      analogWrite(ENB,V3); 
      analogWrite(ENC,V3);
      analogWrite(END,V3);
      }
    if (Data=='C'){
      digitalWrite(IN1,HIGH);      
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      digitalWrite(IN5,HIGH);
      digitalWrite(IN6,LOW);
      digitalWrite(IN7,HIGH);
      digitalWrite(IN8,LOW);
      
      analogWrite(ENA,V3);
      analogWrite(ENB,V3); 
      analogWrite(ENC,V3);
      analogWrite(END,V3);
      }
    if (Data=='D'){
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      digitalWrite(IN5,HIGH);
      digitalWrite(IN6,LOW);
      digitalWrite(IN7,HIGH);
      digitalWrite(IN8,LOW);

      analogWrite(ENA,V2);
      analogWrite(ENB,V2); 
      analogWrite(ENC,V2);
      analogWrite(END,V2);
      }
    if (Data=='E'){
      digitalWrite(IN1,LOW);// Moteur A - Ne pas tourner 
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);// Moteur B - Ne pas tourner
      digitalWrite(IN4,HIGH);
      digitalWrite(IN5,LOW);// Moteur C - Ne pas tourner 
      digitalWrite(IN6,HIGH);
      digitalWrite(IN7,LOW);// Moteur D - Ne pas tourner
      digitalWrite(IN8,HIGH);
      
      analogWrite(ENA,V3);
      analogWrite(ENB,V3); 
      analogWrite(ENC,V3);
      analogWrite(END,V3);
      }
    if (Data=='F'){
      digitalWrite(IN1,LOW);// Moteur A - Ne pas tourner 
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);// Moteur B - Ne pas tourner
      digitalWrite(IN4,HIGH);
      digitalWrite(IN5,LOW);// Moteur C - Ne pas tourner 
      digitalWrite(IN6,HIGH);
      digitalWrite(IN7,LOW);// Moteur D - Ne pas tourner
      digitalWrite(IN8,HIGH);
      
      analogWrite(ENA,V2);
      analogWrite(ENB,V2); 
      analogWrite(ENC,V2);
      analogWrite(END,V2);
      } 
    if (Data=='G'){
      analogWrite(ENA,V0);
      analogWrite(ENB,V0); 
      analogWrite(ENC,V0);
      analogWrite(END,V0);
      }
    }
  } 
}
