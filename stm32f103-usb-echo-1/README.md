# stm32f103-cdc-printf


```c
// file USB_DEVICE/App/usbd_cdc_if.c
/* USER CODE BEGIN PRIVATE_VARIABLES */
+  uint8_t APP_RX_DATA[APP_RX_DATA_SIZE];
/* USER CODE END PRIVATE_VARIABLES */

   /* USER CODE BEGIN 6 */
   USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
   USBD_CDC_ReceivePacket(&hUsbDeviceFS);
+
+  for (uint16_t i=0;i<*Len;i++)
+  {
+    if (Buf[i] == '\r') return ;
+    if (Buf[i] == '\n') return ;
+    APP_RX_DATA[0+i] = Buf[0+i];
+    Buf[i] = '\n';
+  }
+
   return (USBD_OK);
   /* USER CODE END 6 */



// file USB_DEVICE/App/usbd_cdc_if.h
/* USER CODE BEGIN EXPORTED_DEFINES */
+  extern uint8_t APP_RX_DATA[APP_RX_DATA_SIZE];
/* USER CODE END EXPORTED_DEFINES */



// file main.c
 /* USER CODE BEGIN Includes */

+#include "usbd_cdc_if.h"
+#define APP_RX_DATA_SIZE  64
+#define APP_TX_DATA_SIZE  64
+extern uint8_t APP_RX_DATA[];
 /* USER CODE END Includes */

 /* USER CODE BEGIN 0 */

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

   /* USER CODE BEGIN SysInit */

+  USB_DEVICE_PinReset();
   /* USER CODE END SysInit */

   /* USER CODE BEGIN WHILE */
+  uint16_t i;
+  uint16_t len;
   while (1)
   {
+    if(APP_RX_DATA[0] != 0) {
+      printf("data %s \n", APP_RX_DATA);
+      HAL_Delay(5);
+
+      i = 0; len = 0;
+      while(APP_RX_DATA[i]) len = ++i;
+      printf("length %d \n", len);
+      HAL_Delay(5);
+
+      for(uint16_t i =0;i<APP_RX_DATA_SIZE;i++) APP_RX_DATA[i] = 0;
+    }
+
+    HAL_Delay(200);
     /* USER CODE END WHILE */

     /* USER CODE BEGIN 3 */

```
