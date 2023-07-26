# rm_pico_dev

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