#include <SM.h>
#include <State.h>

#include <SPI.h>
#include <Mcp23s17.h>

#define XPAND_1_CS_PIN 2 //Chip Select Pin for the first MCP23S17
MCP23S17 xpand1 = MCP23S17( XPAND_1_CS_PIN, 0x00 );//Address B001

SM STM(S2);

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

State S1(){
  Serial.println("State_1");
  xpand1.port(0xFFFF);
  if(input==0x20 || input==0x21)STM.Set(S0); 
  if(input==0x40 || input==0x41)STM.Set(S2); 
}

State S2(){
  Serial.println("State_2");
  Serial.print(LED_BUILTIN);
//  Serial.println(i);
  i+=0xFF;i%=0xFFFF;
//  i = 0xFFFF;
  xpand1.port(0x1434);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
//  delay(300);
}

int duration, distance = 0;
State S3(){
    Serial.print("State_3:");
    delay(1);
}
