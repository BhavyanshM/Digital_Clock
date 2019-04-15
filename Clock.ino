#include <SM.h>
#include <State.h>

#include <SPI.h>
#include <Mcp23s17.h>

#define XPAND_1_CS_PIN 2 //Chip Select Pin for the first MCP23S17
MCP23S17 xpand1 = MCP23S17( XPAND_1_CS_PIN, 0x00 );//Address B001

SM STM(Clock);

void setup() {
  // put your setup code here, to run once:
  pinMode(XPAND_1_CS_PIN, OUTPUT);//Set CS for first MCP23S17 as output
//  xpand1.pinMode(1, OUTPUT);
//  xpand1.pinMode(2, OUTPUT);
//  xpand1.pinMode(3, OUTPUT);
//  xpand1.pinMode(4, OUTPUT);
//  xpand1.pinMode(5, OUTPUT);
//  xpand1.pinMode(6, OUTPUT);
//  xpand1.pinMode(7, OUTPUT);
//  xpand1.pinMode(8, OUTPUT);
//  xpand1.pinMode(9, OUTPUT);
//  xpand1.pinMode(10, OUTPUT);
//  xpand1.pinMode(11, OUTPUT);
//  xpand1.pinMode(12, OUTPUT);
//  xpand1.pinMode(13, OUTPUT);
//  xpand1.pinMode(14, OUTPUT);
//  xpand1.pinMode(15, OUTPUT);
//  xpand1.pinMode(16, OUTPUT);

  Serial.begin(9600);
  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  xpand1.pinMode(OUTPUT);
  xpand1.port(0xFFFF);

  
 
  
}
int input = 0;
int i = 0;

uint8_t hoursDec = 00;
uint8_t minsDec = 00; 
uint8_t secsDec = 00;

int rightPot = 0;
int leftPot = 0;
int analogRight = 0;
int analogLeft = 0;


void loop() {
//  input = xpand1.port()/256;//Get the MSB of the xpand1 port
//  Serial.println(input, HEX);//Print the MSB of the xpand1 port to the Serial Monitor
  EXEC(STM);//Execute the State machine
}


// State Machines States for STM Start Here
State S0(){
   Serial.println("State_0");
   xpand1.port(0x0000);
}

State Analog(){
  analogRight = analogRead(A1);
  analogLeft = analogRead(A2);

  if(analogRight != rightPot || analogLeft != leftPot){
    rightPot = analogRight;
    leftPot = analogLeft;
    STM.Set(Analog);
  }
}

uint8_t dec2bcd(uint8_t dec)
{
  return (dec/10)*16 + (dec%10);
}


void displayClock(){
  uint8_t hoursDecHigh = hoursDec/5;
  uint8_t hoursDecLow = hoursDec%10;
  uint8_t hoursDecTemp = hoursDecLow*10 + hoursDecHigh;
  uint8_t hours = dec2bcd(hoursDecTemp);  

  uint8_t mins = dec2bcd(minsDec);
  
  uint16_t hours_mins = hours*256 + mins;
  xpand1.port(hours_mins);

  uint8_t secs = dec2bcd(secsDec);
  digitalWrite(7, bitRead(secs,0));
  digitalWrite(8, bitRead(secs,1));
  digitalWrite(9, bitRead(secs,2));
  digitalWrite(10, bitRead(secs,3));
  
  digitalWrite(3, bitRead(secs,4));
  digitalWrite(4, bitRead(secs,5));
  digitalWrite(5, bitRead(secs,6));
  digitalWrite(6, bitRead(secs,7));
}


State Clock(){
  displayClock();

  secsDec++;
  if(secsDec>=60){
    secsDec = 0;
    minsDec++;  
  }
  if(minsDec>=60){
    minsDec = 0;
    hoursDec++;
  }
  if(hoursDec>=24){
    hoursDec = 0;
  }

  analogRight = analogRead(A1);
  analogLeft = analogRead(A2);

  if(analogRight != rightPot || analogLeft != leftPot){
    rightPot = analogRight;
    leftPot = analogLeft;
    STM.Set(Analog);
  }
  
  delay(1000);
}

int duration, distance = 0;
State S3(){
    Serial.print("State_3:");
    delay(1);
}
