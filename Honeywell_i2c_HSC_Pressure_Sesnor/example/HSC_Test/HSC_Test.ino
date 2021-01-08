

#include "HSC.h"
#include "Wire.h"


 HSC PS = HSC(0x28);
void setup()
{
  
 Wire.begin();
 Serial.begin(115200);
 delay(50);
 
  Serial.println("Setting Up Pressure Limits");
 PS.setPmin(-250,"Pa");
 
  Serial.print("Lower Limit Set to "); Serial.print(PS.getPmin("Pa")); Serial.println(" Pa_g");
 PS.setPmax(250,"Pa");
  Serial.print("Upper Limit Set to +"); Serial.print(PS.getPmax("Pa")); Serial.println(" Pa_g");
}


void loop()
{
  PS.measurePressure();
    
  Serial.println("|-----------|");
  Serial.print  ("| Status    | ");  Serial.println(PS.getstatus(), BIN);
  Serial.print  ("| P Data    | ");  Serial.println(PS.getP_bit(), DEC);
  Serial.print  ("| T Data    | ");  Serial.println(PS.getT_bit(), DEC);
  Serial.println("|-----------|");
  Serial.print  ("| P (Pa)    | ");  Serial.println(PS.getP("Pa"),4);
  Serial.print  ("| P (kPa)   | ");  Serial.println(PS.getP("kPa"),7);
  Serial.print  ("| P (MPa)   | ");  Serial.println(PS.getP("MPa"),10);
  Serial.print  ("| P (bar)   | ");  Serial.println(PS.getP("bar"),9);
  Serial.print  ("| P (mbar)  | ");  Serial.println(PS.getP("mbar"),6);
  Serial.print  ("| P (psi)   | ");  Serial.println(PS.getP("psi"),8);
  Serial.print  ("| P (inH20) | ");  Serial.println(PS.getP("inH2O"),10);
  Serial.println("|-----------|");
  Serial.print  ("| T (K)     | ");  Serial.println(PS.getT('K'),4);
  Serial.print  ("| T (°C)    | ");  Serial.println(PS.getT('C'),4);
  Serial.print  ("| T (°R)    | ");  Serial.println(PS.getT('R'),4);
  Serial.print  ("| T (°F)    | ");  Serial.println(PS.getT('F'),4);
  Serial.println("|-----------|");
  Serial.println("");
  delay (500);
}
