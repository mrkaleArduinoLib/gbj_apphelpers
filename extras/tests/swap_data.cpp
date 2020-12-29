/*
  NAME:
  Unit tests of library "gbj_apphelpers" for templated swap function.

  DESCRIPTION:
  The test suite provides test cases for various data types of swapping data
  item pairs.
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

void test_swap_uint16(void)
{
    uint16_t data_1, data_o1, data_2, data_o2;
    data_1 = data_o1 = 0x5555;
    data_2 = data_o2 = 0xAAAA;
    gbj_apphelpers::swapdata(data_1, data_2);
    TEST_ASSERT_EQUAL_UINT16(data_o1, data_2);
    TEST_ASSERT_EQUAL_UINT16(data_o2, data_1);
}

void test_swap_uint8(void)
{
    uint8_t data_1, data_o1, data_2, data_o2;
    data_1 = data_o1 = 0x55;
    data_2 = data_o2 = 0xAA;
    gbj_apphelpers::swapdata(data_1, data_2);
    TEST_ASSERT_EQUAL_UINT8(data_o1, data_2);
    TEST_ASSERT_EQUAL_UINT8(data_o2, data_1);
}

void test_swap_int(void)
{
    int data_1, data_o1, data_2, data_o2;
    data_1 = data_o1 = -12345;
    data_2 = data_o2 = 24321;
    gbj_apphelpers::swapdata(data_1, data_2);
    TEST_ASSERT_EQUAL_INT(data_o1, data_2);
    TEST_ASSERT_EQUAL_INT(data_o2, data_1);
}

void test_swap_float(void)
{
    float data_1, data_o1, data_2, data_o2;
    data_1 = data_o1 = -987654.12;
    data_2 = data_o2 = 123456.98;
    gbj_apphelpers::swapdata(data_1, data_2);
    TEST_ASSERT_EQUAL_FLOAT(data_o1, data_2);
    TEST_ASSERT_EQUAL_FLOAT(data_o2, data_1);
}


void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_swap_uint16);
    RUN_TEST(test_swap_uint8);
    RUN_TEST(test_swap_int);
    RUN_TEST(test_swap_float);

    UNITY_END();
}

void loop(){}