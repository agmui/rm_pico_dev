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
        /**
         * @brief Construct a new Text File object
         * 
         * @param file 
         */
        TextFile(File *file) : fileInterface(file) { read();};
        ~TextFile() { delete fileArr; };

        /**
         * @brief takes raw bytes and saves it in internal char[]
         * 
         * @param buf 
         */
        bool cast(char *buf);

        /**
         * @brief returns char[]
         * 
         * @return char* 
         */
        char* getContents() { return fileArr; };//todo maybe make it return str idk

        /**
         * @brief saves internal buffer to file
         * 
         * @note overwrites the file
         * 
         */
        bool save();

        /**
         * @brief gets file size
         * 
         * @return size_t 
         */
        size_t getSize(){return file->getSize();};
    };
} // namespace debugtools
#endif //  PICO_TEXTFILE_H_