// file usb_printf.c
#include "usb_printf.h"

#define TX_BUFF_LEN 128
uint8_t txBuff[TX_BUFF_LEN];
uint16_t tx_act_pos = 0;

static inline void
buff_clear(void);

int printf(const char *format, ...)
{
  buff_clear();

  va_list arg;
  va_start (arg, format);
  tx_act_pos = vsprintf ((char*) &txBuff[0], format, arg);
  va_end (arg);

  uint8_t result = CDC_Transmit_FS(txBuff, tx_act_pos);
  // @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY

  if (result == USBD_OK) return SUCCESS;
  else return ERROR;
}

static inline void
buff_clear(void)
{
  for(uint16_t i=0; i < TX_BUFF_LEN; i++)
  {
    txBuff[i] = '\0';
  }
  tx_act_pos = 0;
}

void usb_receive(uint8_t* buf, uint32_t len)
{
  uint8_t buffer[20];
  memset(buffer, '\0', 20);
  memcpy(buffer, buf, (size_t) len);
  printf("received %i bytes: %s \n", len, buffer);
}

