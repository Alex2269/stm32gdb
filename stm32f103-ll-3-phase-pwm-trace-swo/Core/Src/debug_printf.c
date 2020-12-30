#include "stm32f1xx.h"

/*
 * Redirect to SWV/SWO
 */
__attribute__((weak))
int _write(int32_t file, uint8_t *ptr, int32_t len)
{
  for (int i = 0; i < len; i++)
    ITM_SendChar((*ptr++));
  return len;
}
