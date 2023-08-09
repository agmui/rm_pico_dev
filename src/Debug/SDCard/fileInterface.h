#ifndef PICO_FILEINTERFACE_H_
#define PICO_FILEINTERFACE_H_

#include "File.h"
#include <iostream>

namespace debugtools
{

    class fileInterface
    {
    protected:
        File *file;
        fileInterface(File *file) : file(file){};

    public:
        virtual ~fileInterface(){};
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
        virtual bool cast(char *buf) = 0;
        virtual bool save() = 0;
    };
}
#endif //  PICO_FILEINTERFACE_H_