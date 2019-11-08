int IRstatus = 0;

void setup() 
  {
  pinMode(52, INPUT);   //Assigns pin 52 as an input
  Serial.begin(9600);   //Begins a serial connection through USB 
  }

void loop() 
  {
  IRstatus = digitalRead(52);    //Read the digital value at pin 52
  Serial.print(IRstatus, BIN);   //Print the digital value to the terminal
  delay(50);
  }
  
