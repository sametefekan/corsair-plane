//Main Reciver Codes
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include<Servo.h>

RF24 radio(2, 4);

const byte adress[6] = "00001";

unsigned long lastReciveTime = 0;
unsigned long currentTime = 0;


Servo ESC;
Servo elevator;
Servo aileron;
Servo rudder;

int ESCvalue, elevatorvalue, aileronvalue, ruddervalue;



struct Data_Package {
  byte jlpotx;
  byte jrpotx;
  byte jrpoty;
  byte potl;
};

Data_Package data;


void setup() {
 Serial.begin(9600);
 radio.begin();
 radio.openReadingPipe(0, adress);
 radio.setDataRate (RF24_2MBPS);
 radio.setPALevel(RF24_PA_MAX);
 radio.startListening();
 
 resetData ();
 ESC.attach(3);
 elevator.attach(5);
 aileron.attach(6);
 rudder.attach(9);
 
}

void loop() {
 currentTime = millis();
 if ( currentTime - lastReciveTime > 1000) {
  
  resetData(); 
 }

 if (radio.available()) {
  radio.read(&data, sizeof(Data_Package));

  lastReciveTime = millis();
 }

 ESCvalue = map(data.potl, 0, 255, 1000, 2000);
  ESC.writeMicroseconds(ESCvalue);
 elevatorvalue = map(data.jrpoty, 0, 255, 0, 80);
  elevator.write(elevatorvalue);
 aileronvalue = map(data.jrpotx, 0, 255, 70, 0);
  aileron.write(aileronvalue);
 ruddervalue = map(data.jlpotx, 0, 255, 70, 0);
  rudder.write(ruddervalue);

}

void resetData() {
  data.jlpotx = 127;
  data.jrpotx = 127;
  data.jrpoty = 127;
  data.potl = 1;
  }
