/*
  NAME:
  gbjAppHelpers

  DESCRIPTION:
  Library with various static methods for typical but generic business logic
  like measurement unit conversions, calculations, etc.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the license GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html
  (related to original code) and MIT License (MIT) for added code.

  CREDENTIALS:
  Author: Libor Gabaj
  GitHub: https://github.com/mrkaleArduinoLib/gbj_apphelpers.git

  CREDITS:
  TimChristopher Laws
  https://github.com/claws/BH1750.git
 */
#ifndef GBJ_APPHELPERS_H
#define GBJ_APPHELPERS_H


class gbj_apphelpers
{
public:
//------------------------------------------------------------------------------
// Public constants
//------------------------------------------------------------------------------
static const String VERSION;


//------------------------------------------------------------------------------
// Calculation
//------------------------------------------------------------------------------
/*
  Calculate dew point temperature.

  DESCRIPTION:
  The method calculates dew point temperature from provided temperature
  and relative humidity.

  PARAMETERS:
  rhum - Ambient relative humidity in per cents.
         - Data type: float
         - Default value: none
         - Limited range: > 0.0

  temp - Ambient temperature in centigrades.
         - Data type: float
         - Default value: none
         - Limited range: > -273.15 and <> -235.66

  RETURN:
  Temperature of dew point in centigrades or unreasonable value -999.0.
*/
static float calculateDewpoint(float rhum, float temp);


//------------------------------------------------------------------------------
// Simple conversion
//------------------------------------------------------------------------------
static inline float convertCelsius2Fahrenheit(float temp) { return (temp * 9.0 / 5.0) + 32.0; };
static inline float convertFahrenheit2Celsius(float temp) { return (temp - 32.0) * 5.0 / 9.0; };

};

#endif
