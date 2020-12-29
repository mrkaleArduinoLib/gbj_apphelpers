/*
  NAME:
  Unit tests of library "gbj_apphelpers" for templated sort functions.

  DESCRIPTION:
  The test suite provides test cases for various data types of sorted data
  buffers.
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

void test_sort_buble_asc_uint16(void)
{
    uint16_t buffer[] = {25, 20, 15, 10, 5, 0};
    uint16_t buffer_e[] = { 0,  5, 10, 15, 20, 25};
    byte dataLen = sizeof(buffer) / sizeof(buffer[0]);
    gbj_apphelpers::sort_buble_asc((uint16_t *)buffer, dataLen);
    TEST_ASSERT_EQUAL_INT16_ARRAY(buffer_e, buffer, dataLen);
}

void test_sort_buble_asc_uint16_reduced(void)
{
    uint16_t buffer[] = {25, 20, 15, 10, 5, 0};
    uint16_t buffer_e[] = {10, 15, 20, 25, 5, 0};
    byte dataLen = sizeof(buffer) / sizeof(buffer[0]);
    gbj_apphelpers::sort_buble_asc((uint16_t *)buffer, 4);
    TEST_ASSERT_EQUAL_INT16_ARRAY(buffer_e, buffer, dataLen);
}

void test_sort_buble_asc_int(void)
{
    int buffer[] = {31999, 20123, 1500, 0, -5, -100, -32000};
    int buffer_e[] = {-32000, -100, -5, 0, 1500, 20123, 31999};
    byte dataLen = sizeof(buffer) / sizeof(buffer[0]);
    gbj_apphelpers::sort_buble_asc((int *)buffer, dataLen);
    TEST_ASSERT_EQUAL_INT16_ARRAY(buffer_e, buffer, dataLen);
}

void test_sort_buble_asc_float(void)
{
    float buffer[] = {25.12, 20.34, 15.56, 10.78, -0.82, -5.91};
    float buffer_e[] = {-5.91, -0.82, 10.78, 15.56, 20.34, 25.12};
    byte dataLen = sizeof(buffer) / sizeof(buffer[0]);
    gbj_apphelpers::sort_buble_asc((float *)buffer, dataLen);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(buffer_e, buffer, dataLen);
}

void test_sort_buble_desc_int(void)
{
    int buffer[] = {-32000, -100, -5, 0, 1500, 20123, 31999};
    int buffer_e[] = {31999, 20123, 1500, 0, -5, -100, -32000};
    byte dataLen = sizeof(buffer) / sizeof(buffer[0]);
    gbj_apphelpers::sort_buble_desc((int *)buffer, dataLen);
    TEST_ASSERT_EQUAL_INT16_ARRAY(buffer_e, buffer, dataLen);
}

void test_sort_buble_desc_int_reduced(void)
{
    int buffer[] = {-32000, -100, -5, 0, 1500, 20123, 31999};
    int buffer_e[] = {1500, 0, -5, -100, -32000, 20123, 31999};
    byte dataLen = sizeof(buffer) / sizeof(buffer[0]);
    gbj_apphelpers::sort_buble_desc((int *)buffer, 5);
    TEST_ASSERT_EQUAL_INT16_ARRAY(buffer_e, buffer, dataLen);
}


void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_sort_buble_asc_uint16);
    RUN_TEST(test_sort_buble_asc_uint16_reduced);
    RUN_TEST(test_sort_buble_asc_int);
    RUN_TEST(test_sort_buble_asc_float);
    RUN_TEST(test_sort_buble_desc_int);
    RUN_TEST(test_sort_buble_desc_int_reduced);

    UNITY_END();
}

void loop(){}