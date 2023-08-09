#ifndef PICO_FILE_H_
#define PICO_FILE_H_

#include "ff_stdio.h"
#include <string>

#define MAX_SIZE 4715 // files can't be bigger than this or else YAML::Load will crash
namespace debugtools
{
    class File
    {
    private:
        std::string name;
        FIL fil;
        FSIZE_t *size; // size is ptr so we dont have to update it
        bool isOpen;

        bool open(BYTE mode);
        bool close();
        bool getRawText(char *buf);

    public:
        File(std::string filename);
        ~File(){};
        bool read(char *buf);
        // virtual bool cast(char *buf) = 0;
        bool overWrite(const char *buf);
        bool append(const char *buf);
        FSIZE_t getSize() { return *size; }; // returns num bytes
        bool fileIsOpen() { return isOpen; };
        FIL *getFilePtr() { return &fil; };
        // bool save(char *buf); // TODO:
    };
} // namespace debugtools

#endif //  PICO_FILE_H_