/*
  NAME:
  Unit tests of library "gbj_apphelpers" for calculating digits in integers.

  DESCRIPTION:
  The test suite provides test cases related to calculating number of digits
  in integer.
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

void test_zero(void)
{
    TEST_ASSERT_EQUAL_UINT8(1, gbj_apphelpers::calculateDigits(0));
}

void test_positive(void)
{
    for (byte i = 8; i < 10; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(i, gbj_apphelpers::calculateDigits(pow(10, i) - 1));
    }
}

void test_negative(void)
{
    for (byte i = 1; i < 10; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(i, gbj_apphelpers::calculateDigits(abs(-1 * (pow(10, i) - 1))));
    }
}


void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_zero);
    RUN_TEST(test_positive);
    RUN_TEST(test_negative);

    UNITY_END();
}

void loop(){}