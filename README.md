# segmentDisplay
Function to output speed/lap/battery/timer to red segment tube displays

Pass data to function as struct. Displays can share the same clock pin (any digital pin) but each one needs its own data pin (any digital pin). 

Speed can be any float up to 9999 (physical limitations of display). Function will round to 0 d.p. If 9999 exceded the display will just stay at 9999. Strange outputs if negative but negative cannot be generated anyway.

Lap can be up to 255. Higher and it rolls over to 0.

Batt is same as lap.

Time is required in ms. The function converts this to mm:ss form. Done so that millis() can be used to time car.
