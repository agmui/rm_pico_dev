#ifndef PICO_TEXTFILE_H_
#define PICO_TEXTFILE_H_

#include "File.h"
#include <string>
#include "fileInterface.h"

namespace debugtools
{

    class TextFile : public fileInterface
    {
    private:
        char *fileArr; // idk fix

    public:
        TextFile(File *file) : fileInterface(file) { read();};
        ~TextFile() { delete fileArr; };
        bool cast(char *buf);
        char* getContents() { return fileArr; };//todo maybe make it return str idk
        bool save();
        size_t getSize(){return file->getSize();};
    };
} // namespace debugtools
#endif //  PICO_TEXTFILE_H_