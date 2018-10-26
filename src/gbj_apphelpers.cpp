#include "gbj_apphelpers.h"
const String gbj_apphelpers::VERSION = "GBJ_APPHELPERS 1.0.0";


float gbj_apphelpers::calculateDewpoint(float rhum, float temp)
{
  // const float A = 8.1332;  // Just for partial pressure calculation
  const float B = 1762.39;
  const float C = 235.66;
  const float NaN = -999.0;
  // Check input parameters
  if (rhum <= 0.0) return NaN;
  if (temp <= -273.15) return NaN;
  if (temp == -1.0 * B) return NaN;
  // Calculate
  float dewpoint = log10(rhum) - 2.0 - (B / (temp + C));
  if (dewpoint == 0) return NaN;
  dewpoint = B / dewpoint + C;
  return -1.0 * dewpoint;
}
