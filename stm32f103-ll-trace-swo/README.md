# stm32f103-ll-trace-swo

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
