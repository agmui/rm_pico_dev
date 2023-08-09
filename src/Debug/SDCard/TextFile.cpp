#include "TextFile.h"
namespace debugtools
{
    bool TextFile::cast(char *buf)
    {
        size_t size = file->getSize();
        fileArr = new char[size];
        // memcpy(fileArr, buf, size);
        strcpy(fileArr, buf);
        return false;
    };

    bool TextFile::save(){
        std::cout << "fileArr: "<< fileArr << std::endl;
        return file->overWrite(fileArr);
    }

} // namespace debugtools
