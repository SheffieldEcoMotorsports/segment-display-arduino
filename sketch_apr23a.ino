#include <TM1637Display.h>

#define DISPLAY_CLK 1 //Set the CLK pin connection to the display. Can be any digital pin
#define SPEED_DISPLAY_DIO 2 //Set the DIO pin connection to the speed display. Can be any digital pin
#define BATT_DISPLAY_DIO 3 
#define LAP_DISPLAY_DIO 4 
#define TIME_DISPLAY_DIO 5  
#define DISPLAY_BRIGHT 7  //set display brightness (7 is max for most but may vary by display)


TM1637Display speed_display(DISPLAY_CLK, SPEED_DISPLAY_DIO);  //set up the speed display
TM1637Display batt_display(DISPLAY_CLK, BATT_DISPLAY_DIO);  //set up the battery display
TM1637Display lap_display(DISPLAY_CLK, LAP_DISPLAY_DIO);  //set up the lap display
TM1637Display time_display(DISPLAY_CLK, TIME_DISPLAY_DIO);  //set up the stopwatch display

struct display_data   //structure passed to displayData fucntion containing data
{
  float spd;
  byte batt;
  byte lap;
  unsigned long t;
};


void displayData(struct display_data *car)
{
  unsigned int tSec, tMin, tMinSec;

  if (car->t<6000000) //prevent clock exceding display limits
  {
    tSec = car->t/1000;  // converts ms to s (truanced)
    if (car->t % tSec>=500)  //round seconds up if neccessary 
    {
      tSec++;
    }
    tMin = tSec/60; //calculates minutes
    tSec %= 60; //calucaltes seconds
    tMinSec = tMin*100 + tSec;  //converts min and sec to format readable by showNumberDecEx
    time_display.showNumberDecEx(tMinSec, B01000000, true); //display time with colon and fill with leading zeros
  }
  else
  {
    time_display.showNumberDec(9999);
  }
  
  if (car->spd < 9999)  //prevent speed exceding display limits
  {
    if (car->spd - (int)car->spd<0.5){
      speed_display.showNumberDec(car->spd);  //display truanced (equivalent of rounding down) value
    }
    else
    {
      speed_display.showNumberDec((int)car->spd+1);  //else round up
    }
  }
  else
  {
    speed_display.showNumberDec(9999);  //max out display
  }

  if (car->batt<101)  //keep battery in limits (0-100%)
  {
    batt_display.showNumberDec(car->batt);
  }
  else
  {
    batt_display.showNumberDec(9999);
  }

  lap_display.showNumberDec(car->lap);
  
}

void setup()
{
  speed_display.setBrightness(DISPLAY_BRIGHT);  //set the diplay to maximum brightness
  batt_display.setBrightness(DISPLAY_BRIGHT);  //set the diplay to maximum brightness
  lap_display.setBrightness(DISPLAY_BRIGHT);  //set the diplay to maximum brightness
  time_display.setBrightness(DISPLAY_BRIGHT);  //set the diplay to maximum brightness

}

void loop()
{
//  struct display_data car;
//  
//  while(1)  //simulates clock at x1000 speed
//  {
//    car.t=millis()*1000;
//    displayData(&car);
//  }

}
