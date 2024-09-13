#include "gbj_apphelpers.h"

float gbj_apphelpers::calculateDewpoint(float rhum, float temp)
{
  // const float A = 8.1332;  // Just for partial pressure calculation
  const float B = 1762.39;
  const float C = 235.66;
  const float NaN = -999.0;
  // Check input parameters
  if (rhum <= 0.0)
    return NaN;
  if (temp <= -273.15)
    return NaN;
  if (temp == -1.0 * B)
    return NaN;
  // Calculate
  float dewpoint = log10(rhum) - 2.0 - (B / (temp + C));
  if (dewpoint == 0)
    return NaN;
  dewpoint = B / dewpoint + C;
  return -1.0 * dewpoint;
}


void gbj_apphelpers::parseDate(Datetime &dtRecord, const char* strDate)
{
  // Parse date "Dec 26 2018"
  dtRecord.year = doubleDigit2Number(&strDate[9]);
  dtRecord.day = doubleDigit2Number(&strDate[4]);
  // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
  switch (strDate[0])
  {
      case 'J':
        if (strDate[1] == 'a')
        {
          dtRecord.month = 1;
        }
        else
        {
          dtRecord.month = (strDate[2] == 'n') ? 6 : 7;
        }
        break;
      case 'F':
        dtRecord.month = 2;
        break;
      case 'A':
        dtRecord.month = (strDate[2] == 'r') ? 4 : 8;
        break;
      case 'M':
        dtRecord.month = (strDate[2] == 'r') ? 3 : 5;
        break;
      case 'S':
        dtRecord.month = 9;
        break;
      case 'O':
        dtRecord.month = 10;
        break;
      case 'N':
        dtRecord.month = 11;
        break;
      case 'D':
        dtRecord.month = 12;
        break;
  }
}


void gbj_apphelpers::parseDateTime(Datetime &dtRecord, \
  const char* strDate, const char* strTime)
{
  parseDate(dtRecord, strDate);
  parseTime(dtRecord, strTime);
}

void gbj_apphelpers::parseDateTime(Datetime &dtRecord,
                                   const __FlashStringHelper *strDate,
                                   const __FlashStringHelper *flashTime)
{
  char buffer[11];
  memcpy_P(buffer, strDate, 11);
  parseDate(dtRecord, buffer);
  memcpy_P(buffer, flashTime, 8);
  parseTime(dtRecord, buffer);
}

String gbj_apphelpers::urlencode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  // char code2;
  for (word i = 0; i < str.length(); i++)
  {
    c = str.charAt(i);
    if (c == ' ')
    {
      encodedString += '+';
    }
    else if (isalnum(c))
    {
      encodedString += c;
    }
    else
    {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9)
      {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9)
      {
        code0 = c - 10 + 'A';
      }
      // code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      // encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}

String gbj_apphelpers::urldecode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  for (word i = 0; i < str.length(); i++)
  {
    c = str.charAt(i);
    if (c == '+')
    {
      encodedString += ' ';
    }
    else if (c == '%')
    {
      i++;
      code0 = str.charAt(i);
      i++;
      code1 = str.charAt(i);
      c = (urldecode_hex2int(code0) << 4) | urldecode_hex2int(code1);
      encodedString += c;
    }
    else
    {

      encodedString += c;
    }
    yield();
  }
  return encodedString;
}
