#ifndef PICO_SDCARD_H__
#define PICO_SDCARD_H__

#include "../src/Debug/SDCard/File.h"
#include <string>
#include <vector>

#include "pico/stdlib.h"
#include <stdio.h>
//
#include "f_util.h"
#include "ff.h"
// #include "ff_stdio.h" //defined in File.h
#include "rtc.h"
//
#include "hw_config.h"

namespace pico
{
    class Drivers;
}

namespace debugtools
{
    class SDCard
    {
    private:
        pico::Drivers *drivers;
        sd_card_t *pSD;
        // File *file;
        // std::string files[];
        bool mounted = false;

    public:
        SDCard(pico::Drivers *drivers) : drivers(drivers) {}
        ~SDCard();
        void init();
        bool mount();
        bool isMounted();
        bool unmount();
        // File* open(std::string filename);
        bool write(File* file);
        bool close(File *file);
        bool deleteFile(std::string filename); //TODO find  out how to delete File obj
        // std::vector<std::string> getFileList();
    };
} // namespace debugtools

#endif //  PICO_SDCARD_H_