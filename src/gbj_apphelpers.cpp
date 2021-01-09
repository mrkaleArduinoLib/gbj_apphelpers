#include "gbj_apphelpers.h"
const String gbj_apphelpers::VERSION = "GBJ_APPHELPERS 1.2.0";


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
