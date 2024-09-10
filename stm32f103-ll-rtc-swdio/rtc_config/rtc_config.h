#ifndef rtc_config_h
#define rtc_config_h

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

struct time_t
{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
};

struct date_t
{
  uint8_t month;
  uint8_t day;
  uint16_t year;
};

extern struct time_t Time;
extern struct time_t Alarm;
extern struct date_t Date;

extern uint8_t EndOfMonth[];
extern uint32_t TimeCounter;

void DATE_Config( uint8_t fMonth, uint8_t fDay, uint16_t fYear);
void DATE_Update(void);
void TIME_Update(void);
void TIME_Config(uint8_t fHour, uint8_t fMin, uint8_t fSec);
void ALARM_Config(uint8_t fHour, uint8_t fMin, uint8_t fSec);


#ifdef __cplusplus
}
#endif

#endif /* rtc_config_h */
