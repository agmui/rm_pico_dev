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
        FSIZE_t size;
        bool isOpen;//todo add logic and checks

        bool open();
        bool close();


    public:
        File(std::string filename) : name(filename), size(getSize()){};
        virtual ~File(){};
        // void setName(std::string name) { this->name = name; };
        FIL *getFilePtr() { return &fil; };
        bool readFile();
        virtual bool cast(char *buf) = 0;
        bool getRawText(char *buf, size_t size);
        bool overWrite(const char *buf);
        bool writeAndClose();                       // todo better name
        FSIZE_t getSize() { return f_size(&fil); }; // returns num bytes
    };
} // namespace debugtools

#endif //  PICO_FILE_H_