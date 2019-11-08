
//load libraries
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Define variables 
#define I2C_ADDR          0x27        //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

//Initialise radio communication
RF24 radio(9, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
int message = 0;



void setup() 
  {
  //Define the LCD as 16 column by 2 rows 
  lcd.begin (16,2);

  //Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
    
  radio.begin();
  radio.openWritingPipe(addresses[0]);            // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
  }
  
void loop() 
  {
  delay(1000);
  radio.startListening();
  if ( radio.available()) 
    {
    while (radio.available()) 
      {
      radio.read(&message, sizeof(message));            //Store received data
 
      //goto first column (column 0) and second line (line 1)
      lcd.setCursor(3,1);
      lcd.print(message);      
      }
  
   
    //delay(5);
    //radio.stopListening();
    //radio.write(&buttonState, sizeof(buttonState));   //Send data
    }
  

  }
