
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

//int message = 0;

int Rx = A1;
int Ry = A0;
char slideSwitch = 3;

int RxStatus;
int RyStatus;
int RxStatus1;
int RyStatus1;
int RxStatus2;
int RyStatus2;
int RxStatus3;
int RyStatus3;

int switchState;
int switchState1;
int switchState2;
int switchState3;

char RxString [5];
char RyString [5];
char switchString [2];
char message [10];


void setup() 
  {
  //Define the LCD as 20 columns by 4 lines 
  lcd.begin (20,4);

  //Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
    
  radio.begin();
  radio.openWritingPipe(addresses[0]);            // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);

  pinMode(Rx, INPUT);
  pinMode(Ry, INPUT);
  pinMode(slideSwitch, INPUT);
  
  Serial.begin(9600);
  }
  
void loop() 
  {
  memset(message, '\0', sizeof(message));
  switchState1 = digitalRead(slideSwitch);
  RxStatus1 = analogRead(Rx);
  RyStatus1 = analogRead(Ry);
  delay(50);

  switchState2 = digitalRead(slideSwitch);
  RxStatus2 = analogRead(Rx);
  RyStatus2 = analogRead(Ry);
  delay(50);

  switchState3 = digitalRead(slideSwitch);
  RxStatus3 = analogRead(Rx);
  RyStatus3 = analogRead(Ry);

  RxStatus = (RxStatus1 + RxStatus2 + RxStatus3) / 3;
  RyStatus = (RyStatus1 + RyStatus2 + RyStatus3) / 3;
  switchState = (switchState1 + switchState2 + switchState3) / 3;

  sprintf(RxString, "%04d", RxStatus);
  sprintf(RyString, "%04d", RyStatus);
  sprintf(switchString, "%01d", switchState);
  
  strcat(message, RxString);
  strcat(message, RyString);
  strcat(message, switchString); 

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(RxStatus);

  lcd.setCursor(0,1);
  lcd.print(RyStatus);

  lcd.setCursor(0,2);
  lcd.print(switchState, BIN);
  
  lcd.setCursor(0,3);
  lcd.print(message);

  radio.stopListening();
  int message = 1234;
  radio.write(&message, sizeof(message));                  //Send data
  
  delay(100);
  radio.startListening();
  if (radio.available()) 
    {
    while (radio.available()) 
      {
      radio.read(&message, sizeof(message));            //Store received data      
      }
      
    }

  }
