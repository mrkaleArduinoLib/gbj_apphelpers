<a id="library"></a>
# gbjAppHelpers
Library with various static methods for typical but generic business logic like measurement unit conversions, calculations, date and time parsing, etc.


<a id="constants"></a>
## Constants
All constants are embedded into the class as static ones including result and error codes except constant defining hardware keypad equipment.

- **gbj\_apphelpers::VERSION**: Name and semantic version of the library.


<a id="usage"></a>
## Usage
The class is not intended to be instantiated. Each method can be called directly as qualified method name, i.e., just with concatenation of the class name scope resolution operator, and method name:

```cpp
  #include "gbj_apphelpers.h"
  float tempF = gbj_apphelpers::convertCelsius2Fahrenheit(20.0);
```

[Back to interface](#interface)


<a id="interface"></a>
## Interface

##### Custom data types
- [Datetime](#Datetime)

#### Calculation
- [calculateDewpoint()](#calculateDewpoint)

#### Conversion
- [convertCelsius2Fahrenheit()](#convertCelsius2Fahrenheit)
- [convertFahrenheit2Celsius()](#convertTemperature)

#### Parsing
- [parseDateTime()](#parseDate)


<a id="Datetime"></a>
## Datetime
#### Description
Custom data type defining the structure of date and time parameters for setting and reading datetime usually to and from real time clock chips.

#### Syntax
    using Datetime = struct
    {
      uint16_t year;
      uint8_t month;
      uint8_t day;
      uint8_t hour;
      uint8_t minute;
      uint8_t second;
      uint8_t weekday;
      bool mode12h;
      bool pm;
    };

#### Parameters
- **year**: Number of a year counting from zero. For setting date only last 2 digits are relevant, that are written to an RTC chip. Corresponding methods reading from RTC chips usually expect 21st century and add 2000 to read two-digit year.
  - *Valid values*: 0 ~ 99
  - *Default value*: 0


- **month**: Number of a month in a year counting from 1 for January.
  - *Valid values*: 1 ~ 12
  - *Default value*: 1


- **day**: Number of a day in a month.
  - *Valid values*: 1 ~ 31
  - *Default value*: 1


- **hour**: Number of an hour in a day.
  - *Valid values*: 0 ~ 23 for 24 hours mode, 1 ~ 12 for 12 hours mode
  - *Default value*: 0


- **minute**: Number of a minute in an hour.
  - *Valid values*: 0 ~ 59
  - *Default value*: 0


- **second**: Number of a second in a minute.
  - *Valid values*: 0 ~ 59
  - *Default value*: 0


- **weekday**: Number of a day in a week. It is up to an application to set the starting day of a week. Usually the first day is Sunday or Monday.
  - *Valid values*: 1 ~ 7
  - *Default value*: 1


- **mode12h**: Flag about using 12 hours mode.
  - *Valid values*: Boolean; true for 12 hours mode, false for 24 hours one
  - *Default value*: false


- **pm**: Flag about past meridiem. It is relevant for 12 hours mode only but is set correctly at reading from an RTC chip at 24 hours mode as well.
  - *Valid values*: Boolean; true for PM, false for AM
  - *Default value*: false

[Back to interface](#interface)


<a id="calculateDewpoint"></a>
## calculateDewpoint()
#### Description
The method calculates dew point temperature from provided ambient relative humidity and temperature.

#### Syntax
    uint8_t calculateDewpoint(float rhum, float temp);

#### Parameters
- **rhum**: Ambient relative humidity in per cent.
  - *Valid values*: rational numbers greater than 0.0
  - *Default value*: none


- **temp**: Ambient temperature in centigrade.
  - *Valid values*: rational numbers greater than -273.15 but other than -235.66
  - *Default value*: none

#### Returns
Dew point temperature in centigrade or the error value -999.0.

[Back to interface](#interface)


<a id="convertTemperature"></a>
## convertCelsius2Fahrenheit(), convertFahrenheit2Celsius()
#### Description
The particular method calculates temperature expressed in one temperature scale to another one as indicates its name.

#### Syntax
    float convertCelsius2Fahrenheit(float temp);
    float convertFahrenheit2Celsius(float temp);

#### Parameters
- **temp**: Temperature in measurement units of source temperature scale.
  - *Valid values*: rational numbers
  - *Default value*: none

#### Returns
Temperature in measurement units of target temperature scale.

[Back to interface](#interface)


<a id="parseDateTime"></a>
## parseDateTime()
#### Description
The method extracts corresponding parts of a date as well as time structure from strings formatted as a compiler __DATE__ and __TIME__ system constants, e.g., "Dec 26 2018" and "12:34:56".
- The method is overloaded, either for flashed constants or for generic strings in SRAM.
- The method does not update [Datetime](#Datetime) members `weekday`, `mode12h`, and `pm`.

#### Syntax
    void parseDateTime(Datetime &dtRecord, const char* strDate, const char* strTime);
    void parseDateTime(Datetime &dtRecord, const __FlashStringHelper* strDate, const __FlashStringHelper* strTime);

#### Parameters
- **dtRecord**: Referenced structure variable for desired date and time.
  - *Valid values*: [Datetime](#Datetime)
  - *Default value*: none


- **strDate**: Pointer to a system date formatted string.
  - *Valid values*: address space
  - *Default value*: none


- **strTime**: Pointer to a system time formatted string.
  - *Valid values*: address space
  - *Default value*: none

#### Returns
None. Indirectly updated referenced variable for datetime structure.

#### Example
```cpp
gbj_apphelpers::Datetime rtcDateTime;
gbj_apphelpers::parseDateTime(rtcDateTime, __DATE__, __TIME__);
gbj_apphelpers::parseDateTime(rtcDateTime, F(__DATE__), F(__TIME__));
```
#### See also
[Datetime](#Datetime)

[Back to interface](#interface)
