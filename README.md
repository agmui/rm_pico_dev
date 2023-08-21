# rm_pico_dev

This is a [taproot](https://github.com/uw-advanced-robotics/taproot) port to work on the pi pico.
taproot github: https://github.com/uw-advanced-robotics/taproot

cloning this repo

```bash
git clone --shallow-submodules https://github.com/agmui/rm_pico_dev.git
cd rm_pico_dev
git submodule update --init
# cd lib/pico-arduino-compat
# git submodule update --init arduino-compat/arduino-pico
# git submodule update --init libs/retroterm
# cd ..
cd pico-sdk
git submodule update --init
```
Also random thing you have to delete or comment out this file in order to build:  
`rm_pico_dev/lib/pico-arduino-compat/arduino-compat/arduino-pico/cores/rp2040/Tone.cpp`

You may also need to change the version of retroTerm to the latest version

---

### to upload:  
read the [sample_rm_pico_app](https://github.com/agmui/sample_rm_pico_app#uploading) uploading section


### libs used
sdk: [pico-sdk](https://github.com/raspberrypi/pico-sdk)  
sd card stuff:[no-OS-FatFS-SD-SPI-RPi-Pico](https://github.com/carlk3/no-OS-FatFS-SD-SPI-RPi-Pico)
[sd card reader](https://www.amazon.com/dp/B07YSD5VTL?psc=1&ref=ppx_yo2ov_dt_b_product_details)  

use any arduino lib with pico-sdk: [pico-arduino-compat](https://github.com/fhdm-dev/pico-arduino-compat)  
canbus: [can2040](https://github.com/KevinOConnor/can2040/blob/master/docs/API.md)
[can node i think? idk](https://www.amazon.com/dp/B00KM6XMXO?psc=1&ref=ppx_yo2ov_dt_b_product_details)

#### PLZ I BEG U PLZ SKIM OVER THE WIKI IT WILL SAVE U SO MUCH TIME

## NOTE:
using the pico sdk along with this lib may mess with things so do it at your own risk

## design thoughts
using the pico lib in code increases coupling

ex: using the uart getc function in remote.cpp
problems it may cause:

* If I expose the pico lib in the app other people trying to use the pico lib and my lib at the same time will have unknown conflicts
* I have to keep track of both the uartID and Uart::UartPort
* increases dependencies and coupling in remote.cpp cuz it needs both pico lib and uart.cpp 

TODO: use `absolute_time_diff_us(t, get_absolute_time()) > 0` for timers

## Features
TODO: add link to wiki
* CLI
* read and write files to sd card
* dji remote
* dji motors
* imu interface
* motor interface
* uart interface
* debugger
* printing to terminal


## TODO:
* some weirdness in DjiMotor.cpp initialize()
* in Motorhandler.cpp addMotorToManager() checking bounds
* RefSerrialData.h MODM_FLAGS8()
* commandMapper in drivers Remote.cpp

* write datalogger
* decided on 1 or 2 canbus
* do a proper port of taproot so the file structure is not cringe
and uses things like modm properly
* get log files to work and fix the read flages in File.cpp
(some weird edge cases gets missed when opining in READ mode or something)
* proply refactor and write an adapter for SD card class mainly
`hw_config.c` and the pSD object
* in SDCard.cpp move time_init() to drivers.h
* decided if file operations should return string or char*
* move Logfile.h, Yaml.h, and TextFile.h to includes folder
* get retroTerm.h to work
* decide if arduino libs going to be used or included i.e. `pico-arduino-compat`
* general TODO statements everywhere
* fix CliFunctions.cpp to be a class
* if doing a re port of taproot also port over the wiki
