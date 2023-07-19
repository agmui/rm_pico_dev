# rm_pico_dev

To read printout:  
`screen /dev/ttyACM0 9600`

### to upload:  
first find what port: `sudo dmesg | tail`
then to upload:  
`sudo mount /dev/sda1 /media/agmui/ ; sudo cp rm_pico_dev.uf2 /media/agmui/ ; sudo umount /media/agmui/`