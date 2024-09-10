#ifndef UART_SDC_SCANF_H_
#define UART_SDC_SCANF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "usbd_cdc_if.h"
#include "main.h"
#include "stdio.h"
#include "stdarg.h"

// This in in one of the headers:
// Це в одному із заголовків:
#define FIFO_SIZE 64 // must be 2^N
#define FIFO_INCR(x) (((x)+1)&((FIFO_SIZE)-1))
/* Structure of FIFO*/
typedef struct FIFO
{
  uint32_t head;
  uint32_t tail;
  uint8_t data[FIFO_SIZE];
} FIFO;

extern FIFO RX_FIFO;

// returns bytes read (could be zero)
// would be easy to make it end early on a stop char (e.g., \r or \n)
// повертає прочитані байти (може бути нулем)
// було б легко зробити так, щоб це закінчилося раніше на символі зупинки (наприклад, \r або \n)
uint8_t VCP_read(uint8_t* Buf, uint32_t Len);

#ifdef __cplusplus
}
#endif

#endif /* UART_SDC_SCANF_H_ */
