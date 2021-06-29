#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int TRIG = 9;      // trigger en pin 9
int ECO = 8;      // echo en pin 8
//int LED = 3;      // LED en pin 3

void setup()
{
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  //pinMode(LED, OUTPUT);   // LED como salida    
  mySoftwareSerial.begin(9600);
  Serial.begin(115200); // inicializacion de comunicacion serial a 9600 bps
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.loop(001);  //Play the first mp3 PROBAR LOOP
}

void loop()
{
   float persona;
    int total=0;
  
  for (int i = 0; i < 22; i++) { //este for recorre las mediciones y las suma. 
    total = ultrasonido() + total; 
    delay(50);
  }
  
  float promedio = total / 22; //aqui se dividen dando el promedio
   persona = promedio / 6,66;
   persona = constrain(persona,0,30);
   myDFPlayer.volume(persona);
   Serial.println(persona);
   
}


int ultrasonido () {
  int DISTANCIA = 0;
  int DURACION;
  digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
  delay(1);       // al pin conectado al trigger
  digitalWrite(TRIG, LOW);    // del sensor

  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
  // alto en Echo
  DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
  return (DISTANCIA);             //devuelve valor del 0 al 30
 
}
