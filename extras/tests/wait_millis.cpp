/*
  NAME:
  Unit tests of library "gbj_apphelpers" for wait function.

  DESCRIPTION:
  The test suite provides test cases for provided waiting interval.
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

void test_wait(void)
{
    unsigned long delay_ms = 1250, timestamp = millis();
    gbj_apphelpers::wait(delay_ms);
    TEST_ASSERT_TRUE((millis() - timestamp) >= delay_ms);
}


void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_wait);

    UNITY_END();
}

void loop(){}