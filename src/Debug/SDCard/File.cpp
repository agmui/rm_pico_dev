#include "File.h"
#include <iostream>
#include "pico/stdlib.h"

#include "f_util.h"
#include "ff.h"
// #include "ff_stdio.h" //defined in File.h
#include "rtc.h"
namespace debugtools
{
    // todo maybe add args for type of read/write
    bool File::open(){
        const char *const f_name = name.c_str();
        FRESULT fr = f_open(getFilePtr(), f_name, FA_WRITE | FA_READ); // "r"
        if (FR_OK != fr && FR_EXIST != fr)
        {
            panic("f_open(%s) error: %s (%d)\n", f_name, FRESULT_str(fr), fr);
            return NULL;
        }
        return false;//todo
    }
    bool File::readFile(){
        //open file
        open();

        // check if its too big
        if(size > MAX_SIZE){
            printf("ERROR: file too big, truncating file\n");
            size = MAX_SIZE;
        }
        //read file
        char buf[size+1];// adding the last char as a \0 may not be needed
        getRawText(buf, size);
        buf[size]='\0';

        //cast to file type
        cast(buf);

        //close file
        close();
        return false;
    }
    bool File::close(){
        FRESULT fr = f_close(getFilePtr());
        if (FR_OK != fr)
        {
            printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
            return false;
        }
        return true;
    }

    bool File::getRawText(char *buf, size_t size)
    {
        // f_gets(buf, size, &fil);//TODO fix second arg
        uint bw;
        f_read(&fil, buf, size, &bw);
        if (bw == 0)
            printf("error: reading file, eof\n"); // TODO make better
        return false;//TODO
    }
    bool File::overWrite(const char *buf)
    {
        //erase everyting in file and open for writing
        FRESULT fr = f_open(&fil, name.c_str(), FA_CREATE_ALWAYS | FA_WRITE | FA_READ); // "w"
        if (FR_OK != fr && FR_EXIST != fr)
        {
            // panic("f_open(%s) error: %s (%d)\n", name.c_str(), FRESULT_str(fr), fr);
            printf("error: f_open\n");
            return false;
        }

        //write to file
        if (f_printf(&fil, buf) < 0)
            printf("error: writing to file"); // TODO make better

        //TODO close right after writing
        close();
        return false;                         // TODO
    }

} // namespace debugtools
