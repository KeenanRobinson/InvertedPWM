# InvertedPWM
Code resources for producing two 1KHz PWM signals, one the inverse of the other for the Arduino Uno/Nano. The purpose of this is to drive an H-bridge circuit, which in turn controls
a servo motor. This due to the fact that the direction of the motor changes according to the PWM, where above 50% the servo-motor moves in the positive direction and less than 50%
causes the motor to move in the negative direction.

## Repository Description

There are two project folders. PWM_controller.ino is setup such that you change the PWM using a constant in the program itself. The PWM_full_controller.ino includes code to output the 
value of the PWM to an LCD screen (1602A) using an I2C library provided by the Arduino IDE. The respective PWM signals, output on D9 and D10 of the Arduino board, are controlled using
a 1K Ohm potentiometer, connected to pin A3. This changes the PWM between 50% and 100%. To change this, alter the map() function in the main loop. 125 is the maximum PWM value (~5V)
and 0 is the minimum (~0V). 62 represents 50% duty cycle. More information is still to come and will be included in this readme. 

## Authors

* **Keenan Robinson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

## Acknowledgments

This code was adapted from the following YouTube video: https://www.youtube.com/watch?v=IMm0-gGkRi0&t=141s
Consider viewing his video in support for his work.
