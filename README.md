# rm_pico_dev

This is a [taproot](https://github.com/uw-advanced-robotics/taproot) port to work on the pi pico.
taproot github: https://github.com/uw-advanced-robotics/taproot

cloning this repo
```bash
git clone --shallow-submodules https://github.com/agmui/rm_pico_dev.git
cd rm_pico_dev
git submodule update --init
cd lib/pico-sdk
git submodule update --init
```

To read printout:  
`screen /dev/ttyACM0 9600`

### to upload:  
first find what port: `sudo dmesg | tail`
then to upload:  
`sudo mount /dev/sda1 /media/agmui/ ; sudo cp rm_pico_dev.uf2 /media/agmui/ ; sudo umount /media/agmui/`

# NOTE:
using the pico sdk along with this lib may mess with things so do it at your own risk

# design thoughts
using the pico lib in code increases coupling

ex: using the uart_getc function in remote.cpp
problems it may cause:
* If I expose the pico lib in the app other people trying to use the pico lib and my lib at the same time will have unknown conflicts
* I have to keep track of both the uartID and Uart::UartPort
* increases dependencies and coupling in remote.cpp cuz it needs both pico lib and uart.cpp 