#ifndef UART_SDC_PRINTF_H_
#define UART_SDC_PRINTF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "usbd_cdc_if.h"
#include "stdio.h"
#include "stdarg.h"

int printf(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* UART_SDC_PRINTF_H_ */
