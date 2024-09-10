# stm32f103-usart-transmit


``` h
    test print message through USART:
    make 
    make debug
```

```h
    setting tty terminal baudrate
    stty -F /dev/ttyACM0 9600 cs8 -cstopb -parity -icanon min 1 time 1
    stty -F /dev/ttyUSB0 9600 cs8 -cstopb -parity -icanon min 1 time 1

    receive:
    cat /dev/ttyACM0
    cat /dev/ttyUSB0

    transmit:
    echo " Hello rs232" > /dev/ttyACM0
    echo " Hello rs232" > /dev/ttyUSB0
```
