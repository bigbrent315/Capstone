#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(49, 48); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;

void setup() 
  {
  radio.begin();
  radio.openWritingPipe(addresses[1]);              //00002
  radio.openReadingPipe(1, addresses[0]);           //00001
  radio.setPALevel(RF24_PA_MIN);                    //Sets signal strength
  }
void loop() 
  {
  delay(1000);
  radio.stopListening();
  int message = 1234;
  radio.write(&message, sizeof(message));                  //Send data
  
  delay(1000);
  radio.stopListening();
  int message2 = 4321;
  radio.write(&message2, sizeof(message2)); 
  //radio.startListening();                           //Begin searching for data
  //while (!radio.available());                       //Proceed if data available
  //radio.read(&buttonState, sizeof(buttonState));    //Store received data
  }
