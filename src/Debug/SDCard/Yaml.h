#ifndef PICO_YAML_H
#define PICO_YAML_H

// TODO: move to includes folder

#include <yaml-cpp/yaml.h>
#include "File.h"
#include <string>
#include "fileInterface.h"

namespace debugtools
{

    class Yaml : public fileInterface
    {
    private:
        YAML::Node node;

    public:
        // using File::File;

        /**
         * @brief Construct a new Yaml object
         * 
         * @param file 
         */
        Yaml(File *file) : fileInterface(file) { read(); };
        ~Yaml(){};

        /**
         * @brief takes raw bytes and turns it into YAML::Node
         * 
         * @param buf 
         */
        bool cast(char *buf);

        /**
         * @brief returns YAML node
         * 
         * @return YAML::Node 
         */
        YAML::Node getNode() { return node; };

        /**
         * @brief converts YAML::Node back into bytes to be saved 
         * 
         * @note overwrites file
         * 
         */
        bool save();
    };

} // namespace debugtools
#endif //  PICO_YAML_H