/*
  NAME:
  Demonstration of gbjAppHelprs librarie's functions.

  DESCRIPTION:
  The sketch provides conversions and calculations built-in in the library.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#define SKETCH "GBJ_APPHELPERS_DEMO 1.0.0"

#include "gbj_apphelpers.h"

float tempValue, rhumValue, dewpValue;


void setup()
{
  Serial.begin(9600);
  Serial.println(SKETCH);
  Serial.println("Libraries:");
  Serial.println(gbj_apphelpers::VERSION);
  Serial.println("---");
  //
  tempValue = 25.0;
  Serial.print("TempC => TempF: ");
  Serial.println(String(tempValue) + " => " + String(gbj_apphelpers::convertCelsius2Fahrenheit(tempValue)));
  //
  tempValue = 77.0;
  Serial.print("TempF => TempC: ");
  Serial.println(String(tempValue) + " => " + String(gbj_apphelpers::convertFahrenheit2Celsius(tempValue)));
  //
  tempValue = 25.0;
  rhumValue = 55.0;
  Serial.print("Rhum, TempC => DewPoint: ");
  Serial.println(String(rhumValue) + ", " + String(tempValue) + " => " + String(gbj_apphelpers::calculateDewpoint(rhumValue, tempValue)));
}


void loop(){}
