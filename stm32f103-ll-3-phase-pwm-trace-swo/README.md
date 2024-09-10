# stm32f103-ll-3-phase-pwm-trace-swo

``` h
  connect 3phase driver to:
  CH1=PA8 ☜--☀--☞ CH1N=PB13
  CH2=PA9 ☜--☀--☞ CH2N=PB14
  CH3=PA10 ☜--☀--☞ CH3N=PB15

  make
  make flash
```

``` h
    # I thought it was convenient to use a terminal multiplexer
    # apt install tmux 
    test printf message through SWO st-link wire:
    sh tmux.run
```

``` h
    it is possible to start two terminals more conveniently
    cd "project dir"
    in one terminal:
    mkfifo itm_swo.fifo ; cat /dev/ttyS0 itm_swo.fifo
    in another terminal:
    make ; make debug
```
