#include <MyoController.h>

#define FIST_PIN 4
#define WAVEIN_PIN 5
#define WAVEOUT_PIN 6
#define FINGERSSPREAD_PIN 7
#define DOUBLETAP_PIN 3
 
MyoController myo = MyoController(); 

// Possibles estats del motor
int horari = 0;
int antihorari = 0 ;
int parar = 0;


//definicion de pins
const int motorPin1 = 8;    // 28BYJ48 In1
const int motorPin2 = 9;    // 28BYJ48 In2
const int motorPin3 = 10;   // 28BYJ48 In3
const int motorPin4 = 11;   // 28BYJ48 In4
                   
//definicion variables
int motorSpeed = 1200;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 4076;  // pasos para una vuelta completa
 
//tablas con la secuencia de encendido (descomentar la que necesiteis)
//secuencia 1-fase
//const int numSteps = 4;
//const int stepsLookup[4] = { B1000, B0100, B0010, B0001 };
 
//secuencia 2-fases
//const int numSteps = 4;
//const int stepsLookup[4] = { B1100, B0110, B0011, B1001 };
 
//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };
 
 
void setup()
{
  //declarar pines como salida
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode (FIST_PIN, OUTPUT); 
  pinMode(DOUBLETAP_PIN, OUTPUT);
  pinMode(WAVEOUT_PIN, OUTPUT);  
    myo.initMyo();
}
 
void loop()
{
/* for (int i = 0; i < stepsPerRev * 2; i++)
  {
    clockwise();
    delayMicroseconds(motorSpeed);
  }
  for (int i = 0; i < stepsPerRev * 2; i++)
  {
    anticlockwise();
    delayMicroseconds(motorSpeed);
  }
  /*delay(1000);
*/  
myo.updatePose();
   switch ( myo.getCurrentPose() ) {
  
  case doubleTap: 
  horari = 0;
  antihorari = 0;
  parar = 1;
  break; 

  case fist: 
  horari = 1;
  antihorari = 0;
  parar = 0 ;
  break;

  case waveOut: 
  horari = 0; 
  antihorari = 1;
  parar = 0;
  break; 
   }


  if (horari ==1) {
    clockwise(); 
    delayMicroseconds(motorSpeed);
    } 
  if (antihorari == 1) {
    anticlockwise();
    delayMicroseconds(motorSpeed);
  }
  if (parar ==1)  ;
}
  
void clockwise()
{
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}
 
void anticlockwise()
{
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter);
}
 
void setOutput(int step)
{
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));

   }

  



