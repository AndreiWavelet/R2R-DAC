/* R2R DAC increment.
 * 
 * Increments the DAC output value every 2 seconds.
 * The R2R DAC is connected to pin 3 (LSb), 4, and 5 (MSb).
 * I will count from 0 to 7 and back to 0.
 * If the electronics were properly built, values at the DAC output will around:
 * 0.00V, 0.62 V, 1.25 V, 1.87 V, 2.50 V, 3.12 V, 3.75 V, 4.37 V, then back to 0.00 V.
 * 
 * Andrei Alves Cardoso, 23/04/2019
 */


#include <r2r_dac.h>

R2R_DAC<3> my_dac;

void setup() {
  //Bit 0 (LSb) goes to pin 3.
  my_dac.SetBitPin(0,3);
  //Bit 1 goes to pin 4.
  my_dac.SetBitPin(1,4);
  //Bit 2 (MSb) goes to pin 5.
  my_dac.SetBitPin(2,5);
}

//Increments DAC value every 2 seconds.
void loop() {
  int current = my_dac.Get();
  my_dac.Set(current+1);
  delay(2000);
}

