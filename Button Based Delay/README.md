# Button Based Delay
This code should have the LED initally blinking at 10 Hz, and have the delay chance based
on how long the button is held down. Unfortunately this code does not function properly.
The timer and button interrupt code is the same as found in button interrupt and Timer A
blink respectively, with the only difference being the value of TACCR0 being 1200 to have
the LED blink at 10 Hz. Instead of delaying based on how long the button is held, the LED
delays to the same rate no matter how long the button is pressed, and if pressed twice, 
the LED will blink at an extremely slow rate.
