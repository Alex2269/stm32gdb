# stm32f103-cdc-printf

```c
diff -Naur stm32f103-cdc-printf/Core/Src/main.c stm32f103-cdc-printf-b/Core/Src/main.c
--- stm32f103-cdc-printf/Core/Src/main.c	2024-09-08 23:43:40.056000000 +0300
+++ stm32f103-cdc-printf-b/Core/Src/main.c	2024-09-08 23:33:20.837890955 +0300
@@ -55,7 +55,15 @@

 /* Private user code ---------------------------------------------------------*/
 /* USER CODE BEGIN 0 */
-
+void USB_DEVICE_PinReset(void)
+{
+  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
+  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_12, LL_GPIO_MODE_OUTPUT);
+  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_12, LL_GPIO_SPEED_FREQ_HIGH);
+  LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_12, LL_GPIO_OUTPUT_PUSHPULL);
+  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_12);
+  LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_12);
+}
 /* USER CODE END 0 */

 /**
@@ -82,20 +90,33 @@
   SystemClock_Config();

   /* USER CODE BEGIN SysInit */
-
+  USB_DEVICE_PinReset();
   /* USER CODE END SysInit */

   /* Initialize all configured peripherals */
   MX_GPIO_Init();
   MX_USB_DEVICE_Init();
   /* USER CODE BEGIN 2 */
-
+  uint8_t array_u8[] = "hello";
+  uint32_t val_integer=1000;
+  float val_float=22.0;
   /* USER CODE END 2 */

   /* Infinite loop */
   /* USER CODE BEGIN WHILE */
   while (1)
   {
+    val_integer++;
+    val_float+=0.25;
+
+    printf(" integer %d \n", val_integer);
+    HAL_Delay(250);
+    printf(" float   %.3f \n", val_float);
+    HAL_Delay(250);
+    printf(" string  %s \n", array_u8);
+    HAL_Delay(250);
+    printf(" %s \n", "bello");
+    HAL_Delay(250);
     /* USER CODE END WHILE */

     /* USER CODE BEGIN 3 */
diff -Naur stm32f103-cdc-printf/Core/usb_printf.c stm32f103-cdc-printf-b/Core/usb_printf.c
--- stm32f103-cdc-printf/Core/usb_printf.c	1970-01-01 03:00:00.000000000 +0300
+++ stm32f103-cdc-printf-b/Core/usb_printf.c	2024-09-08 20:17:57.298643937 +0300
@@ -0,0 +1,44 @@
+// file usb_printf.c
+#include "usb_printf.h"
+
+#define TX_BUFF_LEN 128
+uint8_t txBuff[TX_BUFF_LEN];
+uint16_t tx_act_pos = 0;
+
+static inline void
+buff_clear(void);
+
+int printf(const char *format, ...)
+{
+  buff_clear();
+
+  va_list arg;
+  va_start (arg, format);
+  tx_act_pos = vsprintf ((char*) &txBuff[0], format, arg);
+  va_end (arg);
+
+  uint8_t result = CDC_Transmit_FS(txBuff, tx_act_pos);
+  // @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
+
+  if (result == USBD_OK) return SUCCESS;
+  else return ERROR;
+}
+
+static inline void
+buff_clear(void)
+{
+  for(uint16_t i=0; i < TX_BUFF_LEN; i++)
+  {
+    txBuff[i] = '\0';
+  }
+  tx_act_pos = 0;
+}
+
+void usb_receive(uint8_t* buf, uint32_t len)
+{
+  uint8_t buffer[20];
+  memset(buffer, '\0', 20);
+  memcpy(buffer, buf, (size_t) len);
+  printf("received %i bytes: %s \n", len, buffer);
+}
+
diff -Naur stm32f103-cdc-printf/Core/usb_printf.h stm32f103-cdc-printf-b/Core/usb_printf.h
--- stm32f103-cdc-printf/Core/usb_printf.h	1970-01-01 03:00:00.000000000 +0300
+++ stm32f103-cdc-printf-b/Core/usb_printf.h	2024-09-08 20:17:57.298643937 +0300
@@ -0,0 +1,18 @@
+#ifndef UART_SDC_PRINTF_H_
+#define UART_SDC_PRINTF_H_
+
+#ifdef __cplusplus
+extern "C" {
+#endif
+
+#include "usbd_cdc_if.h"
+#include "stdio.h"
+#include "stdarg.h"
+
+int printf(const char *format, ...);
+
+#ifdef __cplusplus
+}
+#endif
+
+#endif /* UART_SDC_PRINTF_H_ */

```
