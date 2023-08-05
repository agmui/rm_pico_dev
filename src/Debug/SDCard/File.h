#ifndef PICO_FILE_H_
#define PICO_FILE_H_

#include "ff_stdio.h"
class File
{
private:
    FIL *file;

public:
    virtual ~File();
    FIL *getFilePtr(){return file;};
};

#endif //  PICO_FILE_H_