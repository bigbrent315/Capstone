int FWDL = 30;    //Setting up pin numbers with more descriptive names
int BWDL = 31;
int speedL = 8;
int FWDR = 29;
int BWDR = 28;
int speedR = 9;

void setup() 
  {
  pinMode(FWDL, OUTPUT);    //Assining pins to act as outputs 
  pinMode(BWDL, OUTPUT);
  pinMode(speedL, OUTPUT);
  pinMode(FWDR, OUTPUT);
  pinMode(BWDR, OUTPUT);
  pinMode(speedR, OUTPUT);
  }

void loop() 
  {
  analogWrite(speedL, 250);   //Assigns a speed to the motor (0-255) Vmotor=Vin(speedL/255)
  digitalWrite(FWDL, HIGH);   //Dictates the direction of motor rotation
  digitalWrite(BWDL, LOW);

  analogWrite(speedR, 250);   //Same as just above, but for right side motor
  digitalWrite(FWDR, HIGH);
  digitalWrite(BWDR, LOW);

  delay(3000);
  }
