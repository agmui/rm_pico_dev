#include "SDCard.h"
#include "pico/stdlib.h"
#include <iostream>
// #include "../CliFunctions.cpp" //TODO remove code duplication?

namespace debugtools
{
    void SDCard::init()
    {
        time_init();
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

    File *SDCard::open(std::string filename)
    {
        File *file = new File();
        const char *f_name = filename.c_str();
        std::cout << "f_open" << std::endl;
        FRESULT fr = f_open(file->getFilePtr(), f_name, FA_OPEN_APPEND | FA_WRITE);
        std::cout << "after f_open" << std::endl;
        if (FR_OK != fr && FR_EXIST != fr)
        {
            panic("f_open(%s) error: %s (%d)\n", f_name, FRESULT_str(fr), fr);
            return NULL;
        }
        return file;
    }

    // bool SDCard::save(std::string filename)
    // {
    //     return false;
    // }

    bool SDCard::close(File *file)
    {
        FRESULT fr = f_close(file->getFilePtr());
        if (FR_OK != fr)
        {
            printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
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
