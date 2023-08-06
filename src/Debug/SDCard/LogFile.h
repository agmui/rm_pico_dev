#ifndef PICO_LOGFILE_H_
#define PICO_LOGFILE_H_

#include "File.h"
#include <string>

namespace debugtools
{
    

class LogFile
{
private:
    File* file;
public:
    LogFile(File* file) : file(file){};
    ~LogFile();
    bool addToLog(std::string line);
};

} // namespace debugtools
#endif //  PICO_LOGFILE_H_