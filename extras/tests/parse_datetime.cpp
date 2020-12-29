/*
  NAME:
  Unit tests of library "gbj_apphelpers" for datetime structure.

  DESCRIPTION:
  The test suite provides test cases related to datetime structure and its
  utilization.
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

gbj_apphelpers::Datetime dtRecord;

char testDate[] = "Apr 21 2020";
char testTime[] = "21:22:23";


void setup_test()
{
    dtRecord.mode12h = false;
    dtRecord.pm = false;
    gbj_apphelpers::parseDateTime(dtRecord, testDate, testTime);
}

void test_ParseDate(void)
{
    TEST_ASSERT_EQUAL_INT(20, dtRecord.year);
    TEST_ASSERT_EQUAL_INT(4, dtRecord.month);
    TEST_ASSERT_EQUAL_INT(21, dtRecord.day);
}

void test_ParseTime(void)
{
    TEST_ASSERT_EQUAL_INT(21, dtRecord.hour);
    TEST_ASSERT_EQUAL_INT(22, dtRecord.minute);
    TEST_ASSERT_EQUAL_INT(23, dtRecord.second);
}


void setup() {
    setup_test();
    UNITY_BEGIN();

    RUN_TEST(test_ParseDate);
    RUN_TEST(test_ParseTime);

    UNITY_END();
}

void loop(){}