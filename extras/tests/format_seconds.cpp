/*
  NAME:
  Unit tests of library "gbj_apphelpers" for formatting time periods in seconds.

  DESCRIPTION:
  The test suite provides test cases related to various formatting styles.
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

void test_time_hours(void)
{
  TEST_ASSERT_EQUAL_STRING("08:17:05",
                           gbj_apphelpers::formatTimeDay(29825).c_str());
}
void test_time_minutes(void)
{
  TEST_ASSERT_EQUAL_STRING("00:17:05",
                           gbj_apphelpers::formatTimeDay(1025).c_str());
}
void test_time_seconds(void)
{
  TEST_ASSERT_EQUAL_STRING("00:00:05",
                           gbj_apphelpers::formatTimeDay(5).c_str());
}

void test_period_days(void)
{
  TEST_ASSERT_EQUAL_STRING("3d 8h 17m 5s",
                           gbj_apphelpers::formatTimePeriod(289025).c_str());
}
void test_period_hours(void)
{
  TEST_ASSERT_EQUAL_STRING("8h 17m 5s",
                           gbj_apphelpers::formatTimePeriod(29825).c_str());
}
void test_period_minutes(void)
{
  TEST_ASSERT_EQUAL_STRING("17m 5s",
                           gbj_apphelpers::formatTimePeriod(1025).c_str());
}
void test_period_seconds(void)
{
  TEST_ASSERT_EQUAL_STRING("5s", gbj_apphelpers::formatTimePeriod(5).c_str());
}

void test_period_dense_days(void)
{
  TEST_ASSERT_EQUAL_STRING(
    "3d8h17m5s", gbj_apphelpers::formatTimePeriodDense(289025).c_str());
}
void test_period_dense_hours(void)
{
  TEST_ASSERT_EQUAL_STRING(
    "8h17m5s", gbj_apphelpers::formatTimePeriodDense(29825).c_str());
}
void test_period_dense_minutes(void)
{
  TEST_ASSERT_EQUAL_STRING("17m5s",
                           gbj_apphelpers::formatTimePeriodDense(1025).c_str());
}
void test_period_dense_seconds(void)
{
  TEST_ASSERT_EQUAL_STRING("5s",
                           gbj_apphelpers::formatTimePeriodDense(5).c_str());
}

void setup()
{
  UNITY_BEGIN();

  RUN_TEST(test_time_hours);
  RUN_TEST(test_time_minutes);
  RUN_TEST(test_time_seconds);
  RUN_TEST(test_period_days);
  RUN_TEST(test_period_hours);
  RUN_TEST(test_period_minutes);
  RUN_TEST(test_period_seconds);
  RUN_TEST(test_period_dense_days);
  RUN_TEST(test_period_dense_hours);
  RUN_TEST(test_period_dense_minutes);
  RUN_TEST(test_period_dense_seconds);

  UNITY_END();
}

void loop() {}