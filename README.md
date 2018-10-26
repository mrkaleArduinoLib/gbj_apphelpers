<a id="library"></a>
# gbjAppHelpers
Library with various static methods for typical but generic business logic like measurement unit conversions, calculations, etc.


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

#### Calculation
- [calculateDewpoint()](#calculateDewpoint)

#### Conversion
- [convertCelsius2Fahrenheit()](#convertCelsius2Fahrenheit)
- [convertFahrenheit2Celsius()](#convertTemperature)


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
