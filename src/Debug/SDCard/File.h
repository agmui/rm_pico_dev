#ifndef PICO_FILE_H_
#define PICO_FILE_H_

#include "ff_stdio.h"
#include <string>

#define MAX_SIZE 4715 // files can't be bigger than this or else YAML::Load will crash
namespace debugtools
{
    /**
     * @brief inital file class to open files to
     * later be turned into ther file types
     *
     * @note all operations in this class will always open then close the file.
     * This may be slower but if the pico dies mid match the data
     * will most likely be saved.
     *
     */
    class File
    {
        /*
         There is no internal buffer for file. The reason this is that most likely
         the file will be "casted" into another file type so it would be a waist of memory
         to keep a copy of the raw buffer around.
         The buffer to read is in fileInterface.h read().
         */
    private:
        std::string name;
        FIL fil;
        FSIZE_t *size; // size is ptr so we dont have to update it
        bool isOpen;

        bool open(BYTE mode);

        /**
         * @brief
         *
         * @note if you write to the file please always close file
         * or else changes might not be saved
         *
         * @return true
         * @return false
         */
        bool close();
        bool getRawText(char *buf);

    public:
        /**
         * @brief Construct a new File object
         *
         * @note SD card must be mounted first
         *
         * @param filename
         */
        File(std::string filename);
        ~File(){};

        /**
         * @brief reads contents of file and returns the raw contents
         * in char*
         *
         * @note files have a max file size of \p MAX_SIZE
         *
         * @param buf
         * @return true if read worked
         */
        bool read(char *buf);
        // virtual bool cast(char *buf) = 0;

        /**
         * @brief deletes everything in file and overwrites it
         *
         * @param buf
         * @return true if successful else may return false if SD card full
         */
        bool overWrite(const char *buf);

        /**
         * @brief appends \p buf to the end of file
         *
         * @param buf
         * @return true
         * @return false
         */
        bool append(const char *buf);

        /**
         * @brief returns num bytes in file
         *
         * @return FSIZE_t
         */
        FSIZE_t getSize() { return *size; };

        /**
         * @brief returns if file is open
         *
         * @return true if open
         */
        bool fileIsOpen() { return isOpen; }; // TODO this is kinda useless bc files should never be left open

        /**
         * @brief Get the File Ptr for manual file manipulation see ff.h:
         * http://elm-chan.org/fsw/ff/00index_e.html
         *
         * @return FIL*
         */
        FIL *getFilePtr() { return &fil; };
        // bool save(char *buf); // TODO:
    };
} // namespace debugtools

#endif //  PICO_FILE_H_