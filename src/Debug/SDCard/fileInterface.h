#ifndef PICO_FILEINTERFACE_H_
#define PICO_FILEINTERFACE_H_

#include "File.h"
#include <iostream>

namespace debugtools
{

    /**
     * @brief interface for any new file type to be added
     * 
     * the cast() function determins how the raw bytes are interpreted so the 
     * user can just call read().
     * This makes it very easy to add new file types.
     * 
     * 
     */
    class fileInterface
    {
    protected:
        File *file;
        fileInterface(File *file) : file(file){};

    public:
        virtual ~fileInterface(){};

        /**
         * @brief reads specified file type
         * 
         * @note adds \0 at the end of the read buffer so buf is 1 byte bigger than the file
         * @return true 
         * @return false 
         */
        bool read()
        {
            int size = file->getSize();
            char buf[size + 1]; // adding the last char as a \0 may not be needed
            std::cout << "size:" << size << std::endl;
            bool rez = file->read(buf);
            buf[size] = '\0';

            // cast to file type(yaml, txt, log, etc..)
            rez = cast(buf);
            return rez;
        }

        /**
         * @brief must implement this method because it gets called in read().
         * buf is the raw bytes read from the file see Yaml.cpp for example
         * 
         * @param buf 
         * @return true if converted successfully 
         */
        virtual bool cast(char *buf) = 0;

        /**
         * @brief converts what ever inter object back into raw bytes to be saved in the SD card
         * see Yaml.cpp for example
         * 
         * @return true 
         * @return false 
         */
        virtual bool save() = 0;
    };
}
#endif //  PICO_FILEINTERFACE_H_