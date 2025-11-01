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

#include <Arduino.h>
#if defined(__AVR__)
  #include <inttypes.h>
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

  // MCU internal reboot sources
  enum McuReboots : byte
  {
    MCUREBOOT_UNKNOWN,
    MCUREBOOT_ERRORS,
    MCUREBOOT_WIFI,
    MCUREBOOT_WEB,
    MCUREBOOT_GSHEET,
    MCUREBOOT_THERMO,
    MCUREBOOT_THINGSPEAK,
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
    Convert milliseconds to seconds with rounding.

    DESCRIPTION:
    The method calculates seconds from provided milliseconds and round seconds
    to integer mathematically.

    PARAMETERS:
    ms - Milliseconds to be converted.
      - Data type: unsigned long integer
      - Default value: none
      - Limited range: 0 ~ (2^32 - 1)

    RETURN:
    Seconds rounded to integer mathematically.
  */
  static inline uint32_t convertMs2Sec(uint32_t ms)
  {
    return (ms + 500) / 1000;
  }

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
    Convert microcontroller code to textual name.

    DESCRIPTION:
    Provided MCU internal reboot code is translated to a textual representation.

    PARAMETERS:
    code - Microcontroller internal reboot source
    - Data type: McuReboots
    - Default value: none
    - Limited range: none

    RETURN:
    Textual representation of the MCU reboot source.
  */
  static inline String convertReboot2Text(McuReboots code)
  {
    String result;
    switch (code)
    {
      case McuReboots::MCUREBOOT_ERRORS:
        result = F("Permanent Error(s)");
        break;

      case McuReboots::MCUREBOOT_WIFI:
        result = F("Wifi");
        break;

      case McuReboots::MCUREBOOT_WEB:
        result = F("WebServer");
        break;

      case McuReboots::MCUREBOOT_GSHEET:
        result = F("GoogleSpredsheets");
        break;

      case McuReboots::MCUREBOOT_THERMO:
        result = F("Thermometer");
        break;

      case McuReboots::MCUREBOOT_THINGSPEAK:
        result = F("Thingspeak");
        break;

      default:
        result = F("Unknown");
        break;
    }
    return result;
  };

  /*
    Parse compiler day and time format to datetime record.

    DESCRIPTION:
    The method extracts corresponding parts of a day as well as time
    structure from strings formatted as a compiler __DATE__ and __TIME__
    system constants, e.g., "Dec 26 2018" and "12:34:56".
    - The method is overloaded, either for flashed constants or for generic
      strings in SRAM.

    PARAMETERS:
    dtRecord - Referenced structure variable for desired day and time.
      - Data type: gbj_apphelpers::Datetime
      - Default value: none
      - Limited range: address space

    strDate - Pointer to a system day formatted string.
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

  /*
    Format unix epoch time in seconds.

    DESCRIPTION:
    The method formats input seconds as a unix epoch time to date and time
    string all with leading zeros.

    PARAMETERS:
    epochSeconds - Seconds since 01.01.1970 00:00:00.
      - Data type: 32-bit integer

    RETURN:
    String - formatted textual expression of a date and time.
  */
  static inline String formatEpochSeconds(unsigned long epochSeconds)
  {
    // Number of days in month in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long day, month, year, hours, minutes, seconds;
    long daysTillNow, extraTime, extraDays, index, flag = 0;
    // Calculate total days
    daysTillNow = epochSeconds / (24 * 60 * 60);
    extraTime = epochSeconds % (24 * 60 * 60);
    year = 1970;
    // Calculating current year
    while (true)
    {
      if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
      {
        if (daysTillNow < 366)
        {
          break;
        }
        daysTillNow -= 366;
      }
      else
      {
        if (daysTillNow < 365)
        {
          break;
        }
        daysTillNow -= 365;
      }
      year += 1;
    }
    // Updating extradays because it will give days till previous day and we
    // have include current day
    extraDays = daysTillNow + 1;
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    {
      flag = 1;
    }
    // Calculating MONTH and DAY
    month = 0;
    index = 0;
    if (flag == 1)
    {
      while (true)
      {
        if (index == 1)
        {
          if (extraDays - 29 < 0)
          {
            break;
          }
          month += 1;
          extraDays -= 29;
        }
        else
        {
          if (extraDays - daysOfMonth[index] < 0)
          {
            break;
          }
          month += 1;
          extraDays -= daysOfMonth[index];
        }
        index += 1;
      }
    }
    else
    {
      while (true)
      {
        if (extraDays - daysOfMonth[index] < 0)
        {
          break;
        }
        month += 1;
        extraDays -= daysOfMonth[index];
        index += 1;
      }
    }
    // Current Month
    if (extraDays > 0)
    {
      month += 1;
      day = extraDays;
    }
    else
    {
      if (month == 2 && flag == 1)
      {
        day = 29;
      }
      else
      {
        day = daysOfMonth[month - 1];
      }
    }
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    seconds = (extraTime % 3600) % 60;
    // Format output dd.mm.yyyy HH:MM:SS
    char result[42];
    sprintf(result,
            "%02lu.%02lu.%04lu %02lu:%02lu:%02lu",
            day,
            month,
            year,
            hours,
            minutes,
            seconds);
    return result;
  }

  /*
    Format milliseconds to time period.

    DESCRIPTION:
    The method formats input milliseconds to string with days, hours, minutes,
    and seconds ([[x]xd ][[x]xh ][[x]xm ][x]xs).
    - This is the wrapper method for methods 'formatTimePeriod' and
    'convertMs2Sec'.

    PARAMETERS:
    ms - Milliseconds to be converted to seconds and formatted to time period.
      - Data type: unsigned long integer
      - Default value: none
      - Limited range: 0 ~ (2^32 - 1)

    RETURN:
    String - formatted textual expresion of a time period provided in
    milliseconds.
  */
  static inline String formatMsPeriod(uint32_t ms)
  {
    return formatTimePeriod(convertMs2Sec(ms));
  }

  /*
    Provide URL encoding of the string.

    DESCRIPTION:
    The method escapes funny characters in a URL. For example a space is: %20.

    PARAMETERS:
    str - String to be encoded.
    - Data type: String
    - Default value: none
    - Limited range: none

    RETURN:
    URL encoded string.

    CREDIT:
    ESP8266 Hello World urlencode by Steve Nelson.
    https://github.com/zenmanenergy/ESP8266-Arduino-Examples/tree/master/helloWorld_urlencoded
  */
  static String urlencode(String str);

  /*
    Provide URL decoding of the string.

    DESCRIPTION:
    The method converts all URL encoded characters to original funny characters
    from a URL. For example a space is: %20.

    PARAMETERS:
    str - String to be decoded.
    - Data type: String
    - Default value: none
    - Limited range: none

    RETURN:
    URL decoded string.

    CREDIT:
    ESP8266 Hello World urlencode by Steve Nelson.
    https://github.com/zenmanenergy/ESP8266-Arduino-Examples/tree/master/helloWorld_urlencoded
  */
  static String urldecode(String str);

  /**
   * @brief Cummulate long uptime in seconds.
   *
   * @note Uptime in milliseconds beyond the overflow of millis() in 32-bit
   * unsigned long is rounded up to seconds, i.e., every started second is
   * counted.
   * @note The maximum value for millis() is 4294967295 (2^32 - 1), which is
   * about 49.71 days.
   * @note Counting uptime in seconds enables uptime up to 136.1 years.
   * @note Counting uptime seconds starts just at MCU boot and continues forever
   * until MCU is running.
   *
   * @param uptimeMs Uptime in milliseconds.
   *
   * @return Cummulated uptime in seconds.
   *
   */
  static inline unsigned long uptimeSecondsCummulate(unsigned long uptimeMs)
  {
    static unsigned long uptimeSec = 0;
    static unsigned long secLast = 0;
    unsigned long sec = 0;
    // Calculate seconds from milliseconds with rounding
    if (uptimeMs > static_cast<unsigned long>(UINT32_MAX) - 999)
    {
      // Safe fallback to avoid overflow
      sec = uptimeMs / 1000 + 1;
    }
    else
    {
      sec = (uptimeMs + 999) / 1000;
    }
    // Uptime seconds cummulation
    if (sec >= secLast)
    {
      secLast = sec;
    }
    // millis() overflow detected, cummulate seconds
    else
    {
      uptimeSec += secLast;
      secLast = sec;
    }
    return uptimeSec + secLast;
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
    Parse compiler day format to datetime record.

    DESCRIPTION:
    The method extracts corresponding parts of a day structure from string
    formatted as a compiler __DATE__ system constant, e.g., "Dec 26 2018".

    PARAMETERS:
    dtRecord - Referenced structure variable for desired day and time.
    - Data type: gbj_apphelpers::Datetime
    - Default value: none
    - Limited range: address space

    strDate - Pointer to a system day formatted string.
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
    dtRecord - Referenced structure variable for desired day and time.
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

    pressureSea - Sea level barometric pressure in arbitrary measurement unit,
    but the same as the first argument has.
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

  /*
    Convert character to number.

    DESCRIPTION:
    For URL Decoding the method calculates numberic representation of a
    character.

    PARAMETERS:
    c - Converted character
    - Data type: char
    - Default value: none
    - Limited range: none

    RETURN:
    Numeric representation of the character.

    CREDIT:
    ESP8266 Hello World urlencode by Steve Nelson.
    https://github.com/zenmanenergy/ESP8266-Arduino-Examples/tree/master/helloWorld_urlencoded
  */
  static inline byte urldecode_hex2int(char c)
  {
    if (c >= '0' && c <= '9')
    {
      return (static_cast<byte>(c) - '0');
    }
    if (c >= 'a' && c <= 'f')
    {
      return (static_cast<byte>(c) - 'a' + 10);
    }
    if (c >= 'A' && c <= 'F')
    {
      return (static_cast<byte>(c) - 'A' + 10);
    }
    return 0;
  }
};

#endif
