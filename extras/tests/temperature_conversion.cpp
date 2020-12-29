/*
  NAME:
  Unit tests of library "gbj_apphelpers" for temperature.

  DESCRIPTION:
  The test suite provides test cases related to temperature conversion
  and calculation of the dewpoint.
  - The test runner is Unity Project - ThrowTheSwitch.org.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#include <Arduino.h>
#include <unity.h>
#include <gbj_apphelpers.h>

void test_Celsius2Fahrenheit(void)
{
    TEST_ASSERT_EQUAL_FLOAT(68.0, gbj_apphelpers::convertCelsius2Fahrenheit(20.0));
    TEST_ASSERT_EQUAL_FLOAT(77.54, gbj_apphelpers::convertCelsius2Fahrenheit(25.3));
}

void test_Fahrenheit2Celsius(void)
{
    TEST_ASSERT_EQUAL_FLOAT(20.0, gbj_apphelpers::convertFahrenheit2Celsius(68.0));
    TEST_ASSERT_EQUAL_FLOAT(25.3, gbj_apphelpers::convertFahrenheit2Celsius(77.54));
}

void test_Dewpoint(void)
{
    TEST_ASSERT_FLOAT_WITHIN(0.001, 15.36, gbj_apphelpers::calculateDewpoint(55.00, 25.00));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 16.43, gbj_apphelpers::calculateDewpoint(78.40, 20.30));
}


void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_Celsius2Fahrenheit);
    RUN_TEST(test_Fahrenheit2Celsius);
    RUN_TEST(test_Dewpoint);

    UNITY_END();
}

void loop(){}