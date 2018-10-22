# Segment display interfacing with Arduino

Several red segment tube displays will be used to display information to the driver in real time during the competition, such the speed of the vehicle, the amount of battery left, the number of laps completed and a timer.

When multiple displays are being used simultaneously, all displays can share the same clock pin but each display needs its own data pin, which can be any digital pin in the Arduino. Data is passed to the displays as an struct.

Configuration parameters:
 * `Speed` can be any float up to 9999 (physical limitations of display). Function will round to 0 decimal points. If 9999 is exceded the display will just stay at 9999. Note that strange outputs may occur if negative, but a negative value could not be generated anyway.
 * `Lap` can be up to 255. Higher and it rolls over to 0.
 * `Batt` is same as `lap` but an error of 9999 is displayed if 101+ is reached, unless it rolls over.
 * `Time` is required in ms. The function converts this to mm:ss form. Implemented in this manner so that `millis()` can be used to time car.

Code developed by Sheffield Eco Motorsports.