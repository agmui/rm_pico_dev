#include "ff_stdio.h"
class File
{
private:
    FIL *file;

public:
    virtual ~File();
    FIL *getFilePtr(){return file;};
};