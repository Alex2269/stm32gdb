#include "rtc_config.h"
#include "rtc.h"

struct time_t Time;
struct time_t Alarm;
struct date_t Date;

uint32_t TimeCounter;

uint8_t EndOfMonth[12]=
{
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

void DATE_Config( uint8_t fMonth, uint8_t fDay, uint16_t fYear)
{
  Date.month = fMonth;
  Date.day = fDay;
  Date.year = fYear;
}

void DATE_Update(void)
{
  if ((Time.hour == 00) & (Time.min == 00) & (Time.sec == 00))
  {
    if(Date.day == EndOfMonth[Date.month -1])
    {
      Date.day = 1U;
      Date.month += 1U;
    }
    else
    {
      Date.day = Date.day + 1;
    }
    if (Date.month == 13)
    {
      Date.month = 1;
      Date.year += 1;
    }
  }
}

void TIME_Update(void)
{
  TimeCounter = LL_RTC_TIME_Get(RTC);
  Time.hour = (TimeCounter/3600) % 24;
  Time.min = (TimeCounter % 3600) / 60;
  Time.sec = (TimeCounter % 3600) % 60;
}

void TIME_Config(uint8_t fHour, uint8_t fMin, uint8_t fSec)
{
  Time.hour = fHour;
  Time.min = fMin;
  Time.sec = fSec;
  LL_RTC_TIME_Set(RTC,((Time.hour * 3600) + (Time.min * 60) + Time.sec));
}

void ALARM_Config(uint8_t fHour, uint8_t fMin, uint8_t fSec)
{
  Alarm.hour = fHour;
  Alarm.min = fMin;
  Alarm.sec = fSec;
  LL_RTC_ALARM_Set(RTC,((Alarm.hour * 3600) + (Alarm.min * 60) + Alarm.sec));
}
