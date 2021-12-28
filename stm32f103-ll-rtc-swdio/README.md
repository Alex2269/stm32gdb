# stm32f103-ll-rtc-swdio

``` h

time adjustment in rtc.c file:
RTC_InitStruct.AsynchPrescaler = 0x0000FFFU;

  make
  make flash
```

``` h
    test printf message through SWDIO st-link wire:
    make 
    make debug
```
