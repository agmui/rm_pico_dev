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
        Yaml(File *file) : fileInterface(file) { read(); };
        ~Yaml(){};
        bool cast(char *buf);
        YAML::Node getNode() { return node; };
        bool save();
    };

} // namespace debugtools
#endif //  PICO_YAML_H