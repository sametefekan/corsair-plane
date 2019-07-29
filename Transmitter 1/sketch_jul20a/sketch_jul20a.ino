//main trasmitter codes
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
 

RF24 radio(5, 6);

const byte adress[6] = "00001";

struct Data_Package{
  byte jlpotx;
  byte jrpotx;
  byte jrpoty;
  byte potl;
};

Data_Package data;



void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(adress);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

  data.jlpotx = 127;
  data.jrpotx = 127;
  data.jrpoty = 127;
  data.potl = 1;
  
}

void loop() {
   data.jlpotx = map(analogRead(A1), 0, 1023, 0, 255);
   data.jrpotx = map(analogRead(A2), 0, 1023, 0, 255);
   data.jrpoty = map(analogRead(A3), 0, 1023, 0, 255);
   data.potl = map(analogRead(A7), 0, 1023, 0, 255);

   radio.write(&data, sizeof(Data_Package));
}
