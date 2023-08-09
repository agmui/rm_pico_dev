#ifndef PICO_TEXTFILE_H_
#define PICO_TEXTFILE_H_

#include "File.h"
#include <string>

namespace debugtools
{

    class TextFile : public File
    {
    private:
    public:
        using File::File;
        // TextFile(File *file) : file(file){};
        ~TextFile();
        bool cast(char *buf){return false;}; // todo
        std::string getContents();
    };
} // namespace debugtools
#endif //  PICO_TEXTFILE_H_