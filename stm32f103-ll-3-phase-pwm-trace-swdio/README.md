# stm32f103-ll-3-phase-pwm-trace-swdio

``` h
  connect 3phase driver to:
  CH1=PA8 ☜--☀--☞ CH1N=PB13
  CH2=PA9 ☜--☀--☞ CH2N=PB14
  CH3=PA10 ☜--☀--☞ CH3N=PB15

  make
  make flash
```

``` h
    test printf message through SWDIO st-link wire:
    make 
    make debug
```
