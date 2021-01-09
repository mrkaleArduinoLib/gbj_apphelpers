<a id="library"></a>
# gbj_apphelpers
Library with various static methods for typical but generic business logic like measurement unit conversions, calculations, date and time parsing, data sanitizing and manipulation, etc.


<a id="tests"></a>
## Unit testing

The subfolder `tests` in the folder `extras`, i.e., `gbj_apphelpers/extras/test`, contains testing files, usually just one, with unit tests of library [gbj_apphelpers](#library) executable by [Unity](http://www.throwtheswitch.org/unity) test runner. Each testing file should be placed in an individual test folder of a particular project, usually in the structure `test/<testname>/<testfile>`.

* **calculate_digits.cpp**: Test suite providing test cases for determining count of digits in non-negative integers.
* **parse_datetime.cpp**: Test suite providing test cases for datatime strings and structure parsing.
* **sanitize.cpp**: Test suite providing test cases for sanitizing data values with default ones of various data types for valid range.
* **sanitize.cpp**: Test suite providing test cases for sanitizing data values.
* **sort_data.cpp**: Test suite providing test cases for sorting with method buble sorting.
* **swap_data.cpp**: Test suite providing test cases for swapping a pair of data items.
* **temperature_conversion.cpp**: Test suite providing test cases for temperature conversion between Celsius, Farenheit, and Kelvin scales.
* **wait_millis.cpp**: Test suite providing test cases for suspending processing for defining amount of milliseconds.


<a id="constants"></a>
## Constants
All constants are embedded into the class as static ones including result and error codes except constant defining hardware keypad equipment.

* **VERSION**: Name and semantic version of the library.


<a id="usage"></a>
## Usage
The class is not intended to be instantiated. Each method can be called directly as qualified method name, i.e., just with concatenation of the class name scope resolution operator, and method name. For example:

```cpp
  #include "gbj_apphelpers.h"
  float tempF = gbj_apphelpers::convertCelsius2Fahrenheit(20.0);
```


<a id="interface"></a>
## Interface

##### Custom data types

* [Datetime](#Datetime)


#### Data processing

* [sanitize](#sanitize)
* [sort_buble_asc](#sort_buble)
* [sort_buble_desc](#sort_buble)
* [swapdata](#swapdata)


#### Calculation

* [calculateDewpoint()](#calculateDewpoint)
* [calculateDigits()](#calculateDigits)


#### Conversion

* [convertCelsius2Fahrenheit()](#convertTemperature)
* [convertFahrenheit2Celsius()](#convertTemperature)


#### Parsing

* [parseDateTime()](#parseDateTime)


#### Utilities

* [debounce()](#debounce)
* [wait()](#wait)


<a id="Datetime"></a>
## Datetime

#### Description
Custom data type defining the structure of date and time parameters for setting and reading datetime usually to and from real time clock chips.

#### Syntax
    using Datetime = struct Datatime
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
    }

#### Parameters
* **year**: Number of a year counting from zero. For setting date only last 2 digits are relevant, that are written to an RTC chip. Corresponding methods reading from RTC chips usually expect 21st century and add 2000 to read two-digit year.
  * *Valid values*: 0 ~ 99
  * *Default value*: 0


* **month**: Number of a month in a year counting from 1 for January.
  * *Valid values*: 1 ~ 12
  * *Default value*: 1


* **day**: Number of a day in a month.
  * *Valid values*: 1 ~ 31
  * *Default value*: 1


* **hour**: Number of an hour in a day.
  * *Valid values*: 0 ~ 23 for 24 hours mode, 1 ~ 12 for 12 hours mode
  * *Default value*: 0


* **minute**: Number of a minute in an hour.
  * *Valid values*: 0 ~ 59
  * *Default value*: 0


* **second**: Number of a second in a minute.
  * *Valid values*: 0 ~ 59
  * *Default value*: 0


* **weekday**: Number of a day in a week. It is up to an application to set the starting day of a week. Usually the first day is Sunday or Monday.
  * *Valid values*: 1 ~ 7
  * *Default value*: 1


* **mode12h**: Flag about using 12 hours mode.
  * *Valid values*: Boolean; true for 12 hours mode, false for 24 hours one
  * *Default value*: false


* **pm**: Flag about past meridiem. It is relevant for 12 hours mode only but is set correctly at reading from an RTC chip at 24 hours mode as well.
  * *Valid values*: Boolean; true for PM, false for AM
  * *Default value*: false

[Back to interface](#interface)


<a id="calculateDewpoint"></a>
## calculateDewpoint()

#### Description
The method calculates dew point temperature from provided ambient relative humidity and temperature.

#### Syntax
    uint8_t calculateDewpoint(float rhum, float temp)

#### Parameters
* **rhum**: Ambient relative humidity in per cent.
  * *Valid values*: rational numbers greater than 0.0
  * *Default value*: none


* **temp**: Ambient temperature in centigrade.
  * *Valid values*: rational numbers greater than -273.15 but other than -235.66
  * *Default value*: none

#### Returns
Dew point temperature in centigrade or the error value -999.0.

[Back to interface](#interface)


<a id="calculateDigits"></a>
## calculateDigits()

#### Description
The method determines count of digits in an integer number expressed in decimal notation, while zero number is counted as 1 digit.

#### Syntax
    uint8_t calculateDigits(uint32_t number)

#### Parameters
* **number**: Tested non-negative integer.
  * *Valid values*: 0 - (2^32 - 1)
  * *Default value*: none

#### Returns
Number of digits in the integer at decimal notation in range 0 ~ 10.

[Back to interface](#interface)


<a id="convertTemperature"></a>
## convertCelsius2Fahrenheit(), convertFahrenheit2Celsius()

#### Description
The particular method calculates temperature expressed in one temperature scale to another one as indicates its name.

#### Syntax
    float convertCelsius2Fahrenheit(float temp)
    float convertFahrenheit2Celsius(float temp)

#### Parameters
* **temp**: Temperature in measurement units of source temperature scale.
  * *Valid values*: rational numbers
  * *Default value*: none

#### Returns
Temperature in measurement units of target temperature scale.

[Back to interface](#interface)


<a id="debounce"></a>
## debounce()

#### Description
The method reads a <abbr title="General Purpose Input Output">GPIO</abbr> pin until the read value is same as input value.
* The method is considered as a software button debouncing.

#### Syntax
    uint8_t debounce(uint8_t iniVal, uint8_t pin)

#### Parameters
* **iniVal**: Initially read a pin value.
  * *Valid values*: 0 - 255
  * *Default value*: none


* **pin**: GPIO number of a microcontroller with connected button.
  * *Valid values*: 0 - 255
  * *Default value*: none

#### Returns
Steady input value of the pin.

[Back to interface](#interface)


<a id="parseDateTime"></a>
## parseDateTime()

#### Description
The method extracts corresponding parts of a date as well as time structure from strings formatted as a compiler __DATE__ and __TIME__ system constants, e.g., `Dec 26 2018` and `12:34:56`.
* The method is overloaded, either for flashed constants or for generic strings in SRAM.
* The method does not update [Datetime](#Datetime) members `weekday`, `mode12h`, and `pm`.

#### Syntax
    void parseDateTime(Datetime &dtRecord, const char* strDate, const char* strTime)
    void parseDateTime(Datetime &dtRecord, const __FlashStringHelper* strDate, const __FlashStringHelper* strTime)

#### Parameters
* **dtRecord**: Referenced structure variable for desired date and time.
  * *Valid values*: [Datetime](#Datetime)
  * *Default value*: none


* **strDate**: Pointer to a system date formatted string.
  * *Valid values*: address space
  * *Default value*: none


* **strTime**: Pointer to a system time formatted string.
  * *Valid values*: address space
  * *Default value*: none

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


<a id="sanitize"></a>
## sanitize()

#### Description
The method tests input value for valid range defined by minimum and maximum value. If it is outside of the range, method replaces input value with default value.
* Values can be of any comparable data type, but all of the same one.

#### Syntax
    template<class T>
    T sanitize(T valCur, T valDft, T valMin, T valMax)

#### Parameters
* **valCur**: Input tested current value.
* **valDft**: Default value used instead input value for the result.
* **valMin**: Minimal value of a valid range (value space).
* **valMax**: Maximal value of a valid range (value space).

#### Returns
* Input current value if it is inside the valid range.
* Default value if input current value is outside the valid range.

[Back to interface](#interface)


<a id="sort_buble"></a>
## sort_buble_asc(), sort_buble_desc()

#### Description
Corresponding method sorts data items in a provided referenced buffer with help of buble sorting algorithm.
* Values in data buffer can of any comparable data type.

#### Syntax
    template <class T>
    void sort_buble_asc(T *dataBuffer, uint16_t dataLen)
    void sort_buble_desc(T *dataBuffer, uint16_t dataLen)

#### Parameters
* **dataBuffer**: Referenced data buffer with data items of various data type.
  * *Valid values*: for used data type
  * *Default value*: none


* **dataLen**: Number of the first data items in the buffer to sort.
  * *Valid values*: 0 ~ 65535
  * *Default value*: none

#### Returns
None. Indirectly sorted referenced data buffer.

[Back to interface](#interface)


<a id="swapdata"></a>
## swapdata()

#### Description
The method swappes input data items pair upside down.
* Values can be of any data type, but all of the same one.

#### Syntax
    template<class T>
    void swapdata(T &item1, T &item2)

#### Parameters
* **item1**, **item2**: Referenced data items to be swapped.
  * *Valid values*: for used data type
  * *Default value*: none

#### Returns
None. Indirectly swapped values of referenced variables.

[Back to interface](#interface)


<a id="wait"></a>
## wait()

#### Description
The method waits in a loop until input delay expires.
* Method instead `delay()` function utilizes function `millis()`.

#### Syntax
    void wait(uint32_t delay)

#### Parameters
* **delay**: Waiting time period in milliseconds.
  * *Valid values*: 0 ~ (2^32 - 1)
  * *Default value*: none

#### Returns
None.

[Back to interface](#interface)
