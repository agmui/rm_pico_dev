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
    /**
     * @brief
     * A SD card handler that can mount or unmount an SD card.
     * The pinout definitions are in board.h
     * To read or write files go to the File class
     *
     */
    class SDCard
    {
    private:
        pico::Drivers *drivers;
        sd_card_t *pSD;
        // File *file;
        // std::string files[];

    public:
        /**
         * @brief Construct a new SDCard object
         * pinout definitons in board.h
         *
         * @param drivers
         */
        SDCard(pico::Drivers *drivers) : drivers(drivers) {}
        ~SDCard();

        /**
         * @brief
         * searches if for SD card
         */
        void init();

        /**
         * @brief
         * Mounts SD card
         *
         * @return true if mount was successful false if not
         */
        bool mountCard();

        /**
         * @brief checks if SD card is mounted
         * 
         * @return true if it is mounted and false if not 
         */
        bool isMounted() { return pSD->mounted; };

        /**
         * @brief 
         * unmounts SD card
         * 
         * @return if unmounting was successful
         */
        bool unmountCard();

        /**
         * @brief 
         * deletes a file from SD card
         * 
         * /return if delete was successful
         * @param filename name of the file to delete
         * @return true if delete was successful false if not
         */
        bool deleteFile(std::string filename); // TODO:

        /**
         * @brief 
         * makes a new folder in SD card
         * 
         * @return true if folder was made false if not
         */
        bool mkdir();

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        // bool ls();

        // std::vector<std::string> getFileList();
    };
} // namespace debugtools

#endif //  PICO_SDCARD_H_