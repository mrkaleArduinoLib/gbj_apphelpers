/*
  NAME:
  gbjAppHelpers

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
  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
  #include <inttypes.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <Arduino.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif



class gbj_apphelpers
{
  public:

  //----------------------------------------------------------------------------
  // Public constants
  //----------------------------------------------------------------------------
  static const String VERSION;


  //----------------------------------------------------------------------------
  // Public datatypes
  //----------------------------------------------------------------------------
  using Datetime = struct
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


  //----------------------------------------------------------------------------
  // Calculation and manipulation
  //----------------------------------------------------------------------------
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
    Sort buffered values in ascending order.

    DESCRIPTION:
    The method sorts the first number of data items in a provided buffer
    with help of buble sorting algorithm.

    PARAMETERS:
    dataBuffer - Data buffer with data items of various data type.
    dataLen - Number of the first data items in the buffer to sort.
              - Data type: byte
              - Default value: none
              - Limited range: 0 ~ 255

    RETURN: None
  */
  template <class T>
  static void sort_buble_asc(T *dataBuffer, byte dataLen)
  {
    bool again = true;
    for (byte i = 0; i < (dataLen - 1) && again; i++)
    {
      again = false;
      for (byte j = dataLen - 1; j > i; --j)
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
              - Data type: byte
              - Default value: none
              - Limited range: 0 ~ 255

    RETURN: None
  */
  template <class T>
  static void sort_buble_desc(T *dataBuffer, byte dataLen)
  {
    bool again = true;
    for (byte i = 0; i < (dataLen - 1) && again; i++)
    {
      again = false;
      for (byte j = dataLen - 1; j > i; --j)
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


  //----------------------------------------------------------------------------
  // Parsing
  //----------------------------------------------------------------------------
  /*
    Parse compiler date and time format to datetime record.

    DESCRIPTION:
    The method extracts corresponding parts of a date as well as time structure
    from strings formatted as a compiler __DATE__ and __TIME__ system constants,
    e.g., "Dec 26 2018" and "12:34:56".
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
  static void parseDateTime(Datetime &dtRecord, \
    const char* strDate, const char* strTime);
  static void parseDateTime(Datetime &dtRecord, \
    const __FlashStringHelper* strDate, const __FlashStringHelper* strTime);


  //----------------------------------------------------------------------------
  // Formatting
  //----------------------------------------------------------------------------


  //----------------------------------------------------------------------------
  // Utilities
  //----------------------------------------------------------------------------
  static inline float convertCelsius2Fahrenheit(float temp) { return (temp * 9.0 / 5.0) + 32.0; };
  static inline float convertFahrenheit2Celsius(float temp) { return (temp - 32.0) * 5.0 / 9.0; };

  /*
    Wait for a period of time.

    DESCRIPTION:
    The method wait in the loop until input delay expires.

    PARAMETERS:
    delay - Waiting time period in milliseconds.
            - Data type: non-negative integer
            - Default value: none
            - Limited range: 0 ~ 2^32 - 1

    RETURN: none
  */
  static void wait(unsigned long delay);

  /*
    Swap two data items.

    DESCRIPTION:
    The method swappes input data pair upside down.

    PARAMETERS:
    item1, item2 - Data items to be swapped.
                   - Data type: various

    RETURN: none
  */
  template<class T>
  static void swapdata(T &item1, T &item2)
  {
    T temp = item1;
    item1 = item2;
    item2 = temp;
  }


  private:
  //----------------------------------------------------------------------------
  // Private functions
  //----------------------------------------------------------------------------
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
  static uint8_t doubleDigit2Number(const char* p);


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
  static void parseDate(Datetime &dtRecord, const char* strDate);


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
  static void parseTime(Datetime &dtRecord, const char* strTime);

};

#endif
