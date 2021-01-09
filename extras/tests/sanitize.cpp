/*
  NAME:
  Unit tests of library "gbj_apphelpers" for sanitizing numbers.

  DESCRIPTION:
  The test suite provides test cases related to sanitizing numbers of various
  data types for valid range.
  - The test runner is Unity Project - ThrowTheSwitch.org.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#include <Arduino.h>
#include <gbj_apphelpers.h>
#include <unity.h>

void test_byte(void)
{
  uint8_t valCur, valMin = 10, valMax = 20, valDft = (valMax - valMin) / 2;
  //
  valCur = valMin - 1;
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(
    valDft,
    gbj_apphelpers::sanitize(valCur, valDft, valMin, valMax),
    "Below MIN");
  valCur = valMax + 1;
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(
    valDft,
    gbj_apphelpers::sanitize(valCur, valDft, valMin, valMax),
    "Above MAX");
  valCur = (valMax - valMin) / 2;
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(
    valCur,
    gbj_apphelpers::sanitize(valCur, valDft, valMin, valMax),
    "Within RANGE");
}

void test_int(void)
{
  int valCur, valMin = -100, valMax = 200, valDft = (valMax - valMin) / 2;
  //
  valCur = valMin - 1;
  TEST_ASSERT_EQUAL_INT_MESSAGE(
    valDft,
    gbj_apphelpers::sanitize(valCur, valDft, valMin, valMax),
    "Below MIN");
  valCur = valMax + 1;
  TEST_ASSERT_EQUAL_INT_MESSAGE(
    valDft,
    gbj_apphelpers::sanitize(valCur, valDft, valMin, valMax),
    "Above MAX");
  valCur = (valMax - valMin) / 2;
  TEST_ASSERT_EQUAL_INT_MESSAGE(
    valCur,
    gbj_apphelpers::sanitize(valCur, valDft, valMin, valMax),
    "Within RANGE");
}

void test_float(void)
{
  float valCur, valMin = -123.45, valMax = 234.56, valDft = (valMax - valMin) / 2;
  //
  valCur = valMin - 1.95;
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
    valDft,
    gbj_apphelpers::sanitize(valCur, valDft, valMin, valMax),
    "Below MIN");
  valCur = valMax + 1.95;
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
    valDft,
    gbj_apphelpers::sanitize(valCur, valDft, valMin, valMax),
    "Above MAX");
  valCur = (valMax - valMin) / 2.0;
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
    valCur,
    gbj_apphelpers::sanitize(valCur, valDft, valMin, valMax),
    "Within RANGE");
}

void setup()
{
  UNITY_BEGIN();

  RUN_TEST(test_byte);
  RUN_TEST(test_int);
  RUN_TEST(test_float);

  UNITY_END();
}

void loop() {}