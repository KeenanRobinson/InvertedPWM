

/*
The following code is used to control an H-bridge circuit. It produces two
PWM signals, one the inverse of the other, to provide speed control of a servo
motor. Note the design here ensures it stays between 50% duty cycle, where the
servo motor is not moving, and 100% duty cycle, where the servo is moving at 
maximum rated speed in the positive direction.

Created by: Keenan Robinson
Date created: 19/04/2021
*/

/*
Notes:
This is designed for the Arduino Nano. The maximum output it can output is 3.3V
on a given pin. Note this for driving an Arduino Uno, which is 5V.
* sysClk => 16MHz
* Required PWM frequency => ~1KHz
* PWM pins => pin 9,10 (part of timer 1). We use these pins and this timer allows 
the use of the same clock to produce exactly inverted signals.
* clkPrescaler => 64. Used to reduce the clock down from 16MHz. This is primarily
chosen as part of the calculation to get a 1KHz PWM signal.

Calculate PWM frequency:
PWM_frequency = clock_speed / (2 * Prescaler_value * TOP_value)
TOP_value for our mode of operation will be the value of ICR1. 

Mode of operation
*****************
Since this is a motor driver, phase correct mode is suited. Specifically,
the Waveform generation mode 10. 

Prescalar size choices: 1, 8, 64, 256, 1024. The most applicable 
is therefore 64. Subbing into this equation, TOP_value is found to be
125. 
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
//double duty_cycle_const = 30.0; // This duty cycle is present on pin 9. Pin 10 will be 100-duty_cycle
const int POT_PIN = A3;
double duty_cycle = 0.0;

void setup() {
  // put your setup code here, to run once:
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM11);
  //0b10110010
  /*This sets it so OCA1 and OCB1, connected to pin 9 and pin 10, to be inverted
   in comparison to one another. Also sets Waveform generator mode to 10.*/
  TCCR1B = (1 << WGM13) | (1 << CS11) | (1 << CS10); 
  //0b00010011
  /* 
  * This configuration sets waveform generator to mode 10, selecting prescaler to be 64.
  */
  ICR1 = 125; 
  DDRB = (1 << DDB2) | (1 << DDB1);
  // 0b00000110
  // Configure DDR2 and DDR1 to be output mode, for pin 9 and pin 10.

  //*****LCD Setup******
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();  
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Duty cycle: ");
  lcd.setCursor(0,1);
  duty_cycle = map(analogRead(POT_PIN), 0, 1023, 50, 100);
  lcd.print(String(duty_cycle)+" %");
  
  OCR1A = (duty_cycle/100)*125; //Sets the duty cycle for the wavefrom generator, port A
  OCR1B = (duty_cycle/100)*125; //Sets the duty cycle for the wavefrom generator, port A
}
