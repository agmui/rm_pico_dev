#ifndef PICO_TEXTFILE_H_
#define PICO_TEXTFILE_H_

#include "File.h"
#include <string>

namespace debugtools
{

class TextFile
{
private:
    File *file;

public:
    TextFile(File *file) : file(file){};
    ~TextFile();
    std::string getContents();
};
} // namespace debugtools
#endif //  PICO_TEXTFILE_H_