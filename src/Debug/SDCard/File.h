#ifndef PICO_FILE_H_
#define PICO_FILE_H_

#include "ff_stdio.h"
#include <string>

namespace debugtools
{
    class File
    {
    private:
        FIL *fil;
        std::string name;

    public:
        File() : name("no name -_-"){};
        ~File();
        void setName(std::string name) { this->name = name; };
        FIL *getFilePtr() { return fil; };
        void getRawText(char *buf);// TODO: make it a stream or something
    };
} // namespace debugtools

#endif //  PICO_FILE_H_