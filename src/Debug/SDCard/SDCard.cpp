#include "SDCard.h"
#include "pico/stdlib.h"
#include <iostream>
// #include "../CliFunctions.cpp" //TODO remove code duplication?

namespace debugtools
{
    void SDCard::init()
    {
        time_init();//todo put this in drivers or something
        pSD = sd_get_by_num(0);
    }

    bool SDCard::mount()
    {
        FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
        if (FR_OK != fr)
        {
            // TODO: add panic msg somehow
            panic("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
            printf("detected no sd card\n");
            return false;
        }
        return true;
    }

    bool SDCard::unmount()
    {
        FRESULT fr = f_unmount(pSD->pcName);
        if (FR_OK != fr)
        {
            panic("f_unmount error: %s (%d)\n", FRESULT_str(fr), fr);
            printf("unmount err\n");
            return false;
        }
        return true;
    }


    bool SDCard::deleteFile(std::string filename)
    {
        return false;
    }

    // std::vector<std::string> SDCard::getFileList()
    // {
    // }
} // namespace debugtools
