/*
  NAME:
  gbj_apphelpers

  DESCRIPTION:
  Library with various static methods for typical but generic business logic
  like measurement unit conversions, calculations, etc.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the license GNU GPL v3
  http://www.gnu.org/licenses/gpl-3.0.html (related to original code)
  and MIT License (MIT) for added code.

  CREDITS:
  DateTime parsing - JeeLabs http://news.jeelabs.org/code/

  CREDENTIALS:
  Author: Libor Gabaj
  GitHub: https://github.com/mrkaleArduinoLib/gbj_apphelpers.git
*/
#ifndef GBJ_APPHELPERS_H
#define GBJ_APPHELPERS_H

#if defined(__AVR__)
  #include <Arduino.h>
  #include <inttypes.h>
#elif defined(ESP8266)
  #include <Arduino.h>
#elif defined(ESP32)
  #include <Arduino.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif

class gbj_apphelpers
{
public:
  using Datetime = struct Datetime
  {
    uint16_t year = 0;
    uint8_t month = 1;
    uint8_t day = 1;
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t second = 0;
    uint8_t weekday = 1;
    bool mode12h = false;
    bool pm = false;
  };

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

  /*
    Count digits in an non-negative integer number.

    DESCRIPTION:
    The method determines count of digits in an integer number
    in decimal notation.
    - Also zero is counted as 1 digit.

    PARAMETERS:
    val - Counted integer.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: 0 ~ 2^32 - 1

    RETURN:
    Number of digits of an integer in decimal notation.
  */
  static inline uint8_t calculateDigits(uint32_t number)
  {
    uint8_t digits = 0;
    do
    {
      number /= 10;
      digits++;
    } while (number);
    return digits;
  }

  /*
    Convert temperature between Celsius and Fahrenheit.

    DESCRIPTION:
    The particular method calculates temperature expressed in one temperature
    scale to another one as indicates its name.

    PARAMETERS:
    temp - Temperature value.
      - Data type: float
      - Default value: none
      - Limited range: system determined

    RETURN: None
  */
  static inline float convertCelsius2Fahrenheit(float temp)
  {
    return (temp * 9.0 / 5.0) + 32.0;
  };
  static inline float convertFahrenheit2Celsius(float temp)
  {
    return (temp - 32.0) * 5.0 / 9.0;
  };

  /*
    Software button debouncing.

    DESCRIPTION:
    The method reads a GPIO pin until the read value is same as input value.

    PARAMETERS:
    iniVal - Initially read button state.
      - Data type: uint8_t
      - Default value: none
      - Limited range: 0 ~ 255

    pin - GPIO number of a microcontroller with connected button.
      - Data type: uint8_t
      - Default value: none
      - Limited range: 0 ~ 255

    RETURN:
    Stabile input value of the pin.
  */
  static inline uint8_t debounce(uint8_t iniVal, uint8_t pin)
  {
    uint8_t curVal = digitalRead(pin);
    if (iniVal != curVal)
    {
      delay(5);
      curVal = digitalRead(pin);
    }
    return curVal;
  }

  /*
    Parse compiler date and time format to datetime record.

    DESCRIPTION:
    The method extracts corresponding parts of a date as well as time
    structure from strings formatted as a compiler __DATE__ and __TIME__
    system constants, e.g., "Dec 26 2018" and "12:34:56".
    - The method is overloaded, either for flashed constants or for generic
      strings in SRAM.

    PARAMETERS:
    dtRecord - Referenced structure variable for desired date and time.
      - Data type: gbj_apphelpers::Datetime
      - Default value: none
      - Limited range: address space

    strDate - Pointer to a system date formatted string.
      - Data type: char pointer
      - Default value: none
      - Limited range: address range

    strTime - Pointer to a system time formatted string.
      - Data type: char pointer
      - Default value: none
      - Limited range: address range

    RETURN: none
  */
  static void parseDateTime(Datetime &dtRecord,
                            const char *strDate,
                            const char *strTime);
  static void parseDateTime(Datetime &dtRecord,
                            const __FlashStringHelper *strDate,
                            const __FlashStringHelper *strTime);

  /*
    Check value for valid range.

    DESCRIPTION:
    The method tests input value for valid range defined by minimum and
    maximum value.
    - Values can of any comparable data type, but all of the same one.

    PARAMETERS:
    valCur - Checked value.
    valMin, valMax - Values determining a valid range.

    RETURN:
    Boolean flag of validity.
  */
  template<class T>
  static inline bool check(T valCur, T valMin, T valMax)
  {
    if (valCur < valMin || valCur > valMax)
    {
      return false;
    }
    return true;
  }

  /*
    Sanitize value for valid range and default value.

    DESCRIPTION:
    The method tests input value for valid range defined by minimum and
    maximum value. If it is outside of the range, method replaces input value
    with default value.
    - Values can of any comparable data type, but all of the same one.

    PARAMETERS:
    valCur - Sanitized value.
    valDft - Default value.
    valMin, valMax - Values determining a valid range.

    RETURN:
    Current of default value.
  */
  template<class T>
  static inline T sanitize(T valCur, T valDft, T valMin, T valMax)
  {
    if (!check(valCur, valMin, valMax))
    {
      valCur = valDft;
    }
    return valCur;
  }

  /*
    Sort buffered values in ascending order.

    DESCRIPTION:
    The method sorts data items in a provided referenced buffer with help of
    buble sorting algorithm.

    PARAMETERS:
    dataBuffer - Data buffer with data items of various data type.
    dataLen - Number of the first data items in the buffer to sort.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: 0 ~ 65535

    RETURN: None
  */
  template<class T>
  static inline void sort_buble_asc(T *dataBuffer, uint16_t dataLen)
  {
    bool again = true;
    for (uint16_t i = 0; i < (dataLen - 1) && again; i++)
    {
      again = false;
      for (uint16_t j = dataLen - 1; j > i; --j)
      {
        // Next item is lower than previous one
        if (dataBuffer[j] < dataBuffer[j - 1])
        {
          swapdata(dataBuffer[j], dataBuffer[j - 1]);
          again = true;
        }
      }
    }
  }

  /*
    Sort buffered values in descending order.

    DESCRIPTION:
    The method sorts the first number of data items in a provided buffer
    with help of buble sorting algorithm.

    PARAMETERS:
    dataBuffer - Data buffer with data items of various data type.
    dataLen - Number of the first data items in the buffer to sort.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: 0 ~ 65535

    RETURN: None
  */
  template<class T>
  static inline void sort_buble_desc(T *dataBuffer, uint16_t dataLen)
  {
    bool again = true;
    for (uint16_t i = 0; i < (dataLen - 1) && again; i++)
    {
      again = false;
      for (uint16_t j = dataLen - 1; j > i; --j)
      {
        // Next item is greated than previous one
        if (dataBuffer[j] > dataBuffer[j - 1])
        {
          swapdata(dataBuffer[j], dataBuffer[j - 1]);
          again = true;
        }
      }
    }
  }

  /*
    Swap two data items.

    DESCRIPTION:
    The method swappes input data items pair upside down.

    PARAMETERS:
    item1, item2 - Referenced data items to be swapped.
      - Data type: various

    RETURN: none
  */
  template<class T>
  static inline void swapdata(T &item1, T &item2)
  {
    T temp = item1;
    item1 = item2;
    item2 = temp;
  }

  /*
    URL encode string.

    DESCRIPTION:
    The method prepares a string for URL.

    PARAMETERS:
    url - Text for URL or entire one.
      - Data type: String

    RETURN: none
  */
  static inline String urlencode(String url)
  {
    url.replace(" ", "%20");
    return url;
  }

  /*
    Format daily time in seconds.

    DESCRIPTION:
    The method formats input seconds to string with hours, minutes,
    and seconds all with leading zeros (??:??:??).

    PARAMETERS:
    totalSeconds - Seconds since midnight.
      - Data type: 32-bit integer

    RETURN:
    String - formatted textual expression of a time within a day.
  */
  static inline String formatTimeDay(uint32_t totalSeconds)
  {
    char result[9];
    uint8_t seconds = totalSeconds % 60;

    uint32_t totalMinutes = totalSeconds / 60;
    uint8_t minutes = totalMinutes % 60;

    uint32_t totalHours = totalMinutes / 60;
    uint8_t hours = totalHours % 24;

    sprintf(result, "%02u:%02u:%02u", hours, minutes, seconds);
    return result;
  }

  /*
    Format time period in seconds.

    DESCRIPTION:
    The method formats input seconds to string with days, hours, minutes,
    and seconds ([[x]xd ][[x]xh ][[x]xm ][x]xs).

    PARAMETERS:
    totalSeconds - Length of a time period in seconds.
      - Data type: integer

    RETURN:
     String - formatted textual expresion of a time period.
  */
  static inline String formatTimePeriod(uint32_t totalSeconds)
  {
    uint8_t seconds = totalSeconds % 60;

    uint32_t totalMinutes = totalSeconds / 60;
    uint8_t minutes = totalMinutes % 60;

    uint32_t totalHours = totalMinutes / 60;
    uint8_t hours = totalHours % 24;

    uint32_t days = totalHours / 24;

    String result = "";
    if (days > 0)
    {
      result += String(days) + "d ";
    }
    if (result.length() > 0 || hours > 0)
    {
      result += String(hours) + "h ";
    }
    if (result.length() > 0 || minutes > 0)
    {
      result += String(minutes) + "m ";
    }

    return result + String(seconds) + "s";
  }

  /*
    Format time period in seconds without spaces.

    DESCRIPTION:
    The method formats input seconds to string with days, hours, minutes,
    and seconds ([[x]xd][[x]xh][[x]xm][x]xs).

    PARAMETERS:
    totalSeconds - Length of a time period in seconds.
      - Data type: integer

    RETURN:
    String - formatted textual expresion of a time period.
  */
  static inline String formatTimePeriodDense(uint32_t totalSeconds)
  {
    String result = formatTimePeriod(totalSeconds);
    result.replace(" ", "");
    return result;
  }

private:
  /*
    Convert double digit to number.

    DESCRIPTION:
    The method calculates number from pointed double character, which is
    expected to be a double digit string.

    PARAMETERS:
    p - Pointer to characters.
      - Data type: char pointer
      - Default value: none
      - Limited range: address range

    RETURN:
    Number converted from double digit string.
  */
  static inline uint8_t doubleDigit2Number(const char *p)
  {
    uint8_t num = 0;
    if ('0' <= *p && *p <= '9')
      num = *p - '0';
    return 10 * num + *++p - '0';
  }

  /*
  Parse compiler date format to datetime record.

  DESCRIPTION:
  The method extracts corresponding parts of a date structure from string
  formatted as a compiler __DATE__ system constant, e.g., "Dec 26 2018".

  PARAMETERS:
  dtRecord - Referenced structure variable for desired date and time.
  - Data type: gbj_apphelpers::Datetime
  - Default value: none
  - Limited range: address space

  strDate - Pointer to a system date formatted string.
  - Data type: char pointer
  - Default value: none
  - Limited range: address range

  RETURN: none
  */
  static void parseDate(Datetime &dtRecord, const char *strDate);

  /*
  Parse compiler time format to datetime record.

  DESCRIPTION:
  The method extracts corresponding parts of a time structure from string
  formatted as a compiler __TIME__ system constant, e.g., "12:34:56".

  PARAMETERS:
  dtRecord - Referenced structure variable for desired date and time.
  - Data type: gbj_apphelpers::Datetime
  - Default value: none
  - Limited range: address space

  strTime - Pointer to a system time formatted string.
  - Data type: char pointer
  - Default value: none
  - Limited range: address range

  RETURN: none
  */
  static inline void parseTime(Datetime &dtRecord, const char *strTime)
  {
    // Parse time "12:34:56"
    dtRecord.hour = doubleDigit2Number(&strTime[0]);
    dtRecord.minute = doubleDigit2Number(&strTime[3]);
    dtRecord.second = doubleDigit2Number(&strTime[6]);
  }

  /*
  Calculate altitude from barometric pressures.

  DESCRIPTION:
  The method calculates local altitude from provided local barometric pressure
  and corresponding sea level pressure.
  - Both input pressures should be in the same measurement unit. However that
  unit can be arbitrary, usually Pascal or hectoPascal.

  PARAMETERS:
  pressure - Local barometric pressure in arbitrary measurement unit, usually
  Pascal or hectoPascal.
  - Data type: decimal
  - Default value: none
  - Limited range: none

  pressureSea - Sea level barometric pressure in arbitrary measurement unit, but
  the same as the first argument has.
  - Data type: decimal
  - Default value: none
  - Limited range: none

  RETURN:
  Altitude in meters.
  */
  static inline float calculateAltitudeFromPressures(float pressure,
                                                     float pressureSea)
  {
    return 44330.0 * (1.0 - pow(pressure / pressureSea, (1.0 / 5.255)));
  }

  /*
  Calculate sea level barometric pressures.

  DESCRIPTION:
  The method calculates barometric pressure at sea level from provided local
  pressure and altitude.
  - The measurement unit of the local pressure can be arbitrary. However the
  methods returns the sea level pressure in the same unit.

  PARAMETERS:
  pressure - Local barometric pressure in arbitrary measurement unit, usually
  Pascal or hectoPascal.
  - Data type: decimal
  - Default value: none
  - Limited range: none

  altitude - Local altitude in meters for which the equivalent sea level
  pressure should be calculated.
  - Data type: decimal
  - Default value: none
  - Limited range: none

  RETURN:
  Barometric pressure at sea level.
  */
  static inline float calculatePressureSeaFromAltitude(float pressure,
                                                       float altitude)
  {
    return pressure / pow(1.0 - altitude / 44330.0, 5.255);
  }
};

#endif
