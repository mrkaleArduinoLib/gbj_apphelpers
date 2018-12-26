/*
  NAME:
  Demonstration of datetime parsing by gbjAppHelpers library.

  DESCRIPTION:
  The sketch provides parsing of the compiler date and time.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#define SKETCH "GBJ_APPHELPERS_DATETIME 1.0.0"

#include "gbj_apphelpers.h"

gbj_apphelpers::Datetime dtRecord;


void setup()
{
  Serial.begin(9600);
  Serial.println(SKETCH);
  Serial.println("Libraries:");
  Serial.println(gbj_apphelpers::VERSION);
  Serial.println("---");
  //
  gbj_apphelpers::parseDateTime(dtRecord, __DATE__, __TIME__);
  // Date
  Serial.print("Date: ");
  Serial.print((dtRecord.day < 10 ? "0" : "") + String(dtRecord.day) + ".");
  Serial.print((dtRecord.month < 10 ? "0" : "") + String(dtRecord.month) + ".");
  Serial.println(dtRecord.year);
  // Time
  Serial.print("Time: ");
  Serial.print((dtRecord.hour < 10 ? "0" : "") + String(dtRecord.hour) + ":");
  Serial.print((dtRecord.minute < 10 ? "0" : "") + String(dtRecord.minute) + ":");
  Serial.println((dtRecord.second < 10 ? "0" : "") + String(dtRecord.second));
  Serial.println("---");
  Serial.println("END");
}


void loop(){}
