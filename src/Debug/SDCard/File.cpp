#include "File.h"
#include <iostream>
#include "pico/stdlib.h"

#include "f_util.h"
#include "ff.h"
// #include "ff_stdio.h" //defined in File.h
#include "rtc.h"
namespace debugtools
{
    bool File::open(BYTE mode)
    {
        if (isOpen)
            printf("WARNING: %s already open?\n", name);
        isOpen = true;

        const char *const f_name = name.c_str();
        FRESULT fr = f_open(getFilePtr(), f_name, mode); // "r"
        if (FR_OK != fr && FR_EXIST != fr)
        {
            panic("f_open(%s) error: %s (%d)\n", f_name, FRESULT_str(fr), fr);
            return false;
        }
        return true;
    }

    bool File::readFile()
    {
        bool rez = true;
        // open file
        rez = open(FA_WRITE | FA_READ);

        // check if its too big
        if (size > MAX_SIZE)
        {
            printf("ERROR: file too big, truncating file\n");
            size = MAX_SIZE;
        }
        // read file
        char buf[size + 1]; // adding the last char as a \0 may not be needed
        rez = getRawText(buf, size);
        buf[size] = '\0';

        // cast to file type
        rez = cast(buf);

        // close file
        rez = close();
        return rez;
    }

    bool File::getRawText(char *buf, size_t size)
    {
        uint bw; // bytes read
        f_read(&fil, buf, size, &bw);
        if (bw == 0) // if no bytes read
        {
            printf("ERROR: in getRawText(), maybe noting in file\n");
            return false;
        }
        return true;
    }

    bool File::close()
    {
        if (!isOpen)
            printf("WARNING: %s not open?\n", name);
        isOpen = false;

        FRESULT fr = f_close(getFilePtr());
        if (FR_OK != fr)
        {
            printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
            return false;
        }
        return true;
    }

    // TODO: add cap to write to size?
    bool File::overWrite(const char *buf)
    {
        // erase everyting in file and open for writing
        bool rez = true;
        rez = open(FA_CREATE_ALWAYS | FA_WRITE | FA_READ);

        // write to file
        if (f_printf(&fil, buf) < 0)
        {
            printf("ERROR: in overWrite(), disk maybe full ");
            rez = false;
        }

        rez = close();
        return rez;
    }

} // namespace debugtools
