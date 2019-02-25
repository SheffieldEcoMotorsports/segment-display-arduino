// include servo, bluetooth and h bridge libraries 
#include <SoftwareSerial.h>
//#include <SparkFun_TB6612.h>
#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define DISPLAY_CLK 8 
#define SPEED_DISPLAY_DIO 7 //speed display
#define BATT_DISPLAY_DIO 3 //battery display
#define LAP_DISPLAY_DIO 4 //lap number display
#define TIME_DISPLAY_DIO 5 //time display
#define TEST_DELAY   1000

TM1637Display speed_display(DISPLAY_CLK, SPEED_DISPLAY_DIO);  //set up the speed display
TM1637Display batt_display(DISPLAY_CLK, BATT_DISPLAY_DIO);  //set up the battery display
TM1637Display lap_display(DISPLAY_CLK, LAP_DISPLAY_DIO);  //set up the lap display
TM1637Display time_display(DISPLAY_CLK, TIME_DISPLAY_DIO);  //set up the stopwatch display

//bluetooth set up pins
SoftwareSerial BTserial(11,12); // Arduino-RX | Arduino-TX
// Variable set up for servo

//global variable declaration
char incomingControl; //a variable to read incoming serial data
String Str = "";
int i=40;
int j;

void setup()
{
  // pinMode(12,OUTPUT); //green LED
//  pinMode(13,OUTPUT); //red LED
  //sets up PWM
  Serial.begin(9600);
  
  
  // Bluetooth Set Up
  BTserial.begin(9600); //Start with BTbaudRate
  BTserial.print("AT");   //Check connection (Should return msg "OK")
    delay(1000);      //Backoff time of 1 sec as per datasheet     
   if (BTserial.available()>0)
    {
      while(BTserial.available()>0){
        char c = BTserial.read();
        Serial.write(c);
        }
    }
    BTserial.print("AT+NAMECereal_bus");   //Set name (Should return msg "OKsetname")
    delay(1000);    //Backoff time to receive msg
   if (BTserial.available()>0)
    {
      while(BTserial.available()>0){
        char c = BTserial.read();
        Serial.write(c);
        }
    } 
    BTserial.print("AT+PIN5678");       //Set pin (Should return msg "OKsetPIN");
    delay(1000);//Backoff time of 1 sec as per datasheet    
    if (BTserial.available()>0)
    {
      while(BTserial.available()>0){
        char c = BTserial.read();
        Serial.write(c);
        }
    }
}


void loop()
{
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  speed_display.setBrightness(0x0f);
  batt_display.setBrightness(0x0f);
  lap_display.setBrightness(0x0f);
  time_display.setBrightness(0x0f);


//  // All segments on
//  display1.setSegments(data);
//  display2.setSegments(data);
//  display3.setSegments(data);
//  delay(TEST_DELAY);

//for (j=1; j <= 3; j++){
// Show decimal numbers with/without leading zeros
 // speed_display.showNumberDecEx(0,B01000000, false); // Expect: ___0, if colon on, turn 7 bit to 0 and false to true
//  batt_display.showNumberDec(1, false);
//  lap_display.showNumberDec(2, false);
//  time_display.showNumberDec(3, false);
 // delay(TEST_DELAY);
  //speed_display.showNumberDec(1, false); // Expect: ___1
//  batt_display.showNumberDec(2, false);
//  lap_display.showNumberDec(3, false);
//  time_display.showNumberDec(4, false);
 // delay(TEST_DELAY);
  //speed_display.showNumberDec(2, false);  // Expect: 0002
//  batt_display.showNumberDec(3, false);
//  lap_display.showNumberDec(4, false);
//  time_display.showNumberDec(5, false);
  //delay(TEST_DELAY);
  //speed_display.showNumberDec(3, false);
//  batt_display.showNumberDec(4, false);// Expect: 0003
//  lap_display.showNumberDec(5, false);
//  time_display.showNumberDec(6, false);
  //delay(TEST_DELAY);
  // for loop for servo angle to be written moving left
  
     if(BTserial.available() > 0) // triggered if something new is printed in bluetooth COM port
     { 
      Str = "";
      while(BTserial.available() > 0)
      {
         // read the newest byte in the serial buffer:
         incomingControl = BTserial.read();
         Str = Str + incomingControl;
      }
         Serial.println(Str);
         //Serial.println(Index1);
         //Serial.println(incomingControl);
          //If serial reads 1, car moves backwards
          // *** PLEASE NOTE all of the motion commands are reversed due to the configuration of the remote and the set up of motors***
         //if (incomingControl == '1')
         {
            speed_display.showNumberDecEx(Str.toInt(),B01000000, false); 
          // delay(1000);
//            speed_display.showNumberDecEx(1,B01000000, false);
//            delay(1000);
//            speed_display.showNumberDecEx(2,B01000000, false); 
//            delay(1000);
//            speed_display.showNumberDecEx(3,B01000000, false); 
//            delay(1000);
//            Serial.println("1");
//          forward(motor1, motor2, 200); //backward
         }
//         else if (incomingControl == '0')
//         {
//            digitalWrite(12,LOW); //1 LED off
//            delay(1000);
//            Serial.println("0");
//          //left(motor1, motor2, 200); //right
//         }
//         else if (incomingControl == '3')
//         {
//           right(motor1, motor2, 200); // left
//         }
//         else if (incomingControl == '4')
//         {
//            back(motor1, motor2, 200); // forward
//         }
//          else if (incomingControl == '5')
//         {
//            digitalWrite(12,HIGH); //1 LED on
//            delay(100);
//         }
//          else if (incomingControl == '6')
//         {
//            digitalWrite(13,HIGH); //1 LED on
//            delay(100);
//         }
//         else if (incomingControl == 'X' || incomingControl == 'x')
//         {
//          brake(motor1, motor2); // this does in fact brake and not coast the vehicle
//          digitalWrite(12,LOW); //LED's off
//          digitalWrite(13,LOW);
//         }
//     }
  }
}
