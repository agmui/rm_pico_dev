#ifndef PICO_YAML_H
#define PICO_YAML_H

#include "yaml-cpp/yaml.h"
#include "File.h"

namespace debugtools
{
    
class Yaml
{
private:
    File* file;
    // YAML::Node node;

public:
    Yaml(File* file);// : node(YAML::Load(file->getRawText())){};
    ~Yaml();
    // YAML::Node getYamlFile(){return node;};
};

} // namespace debugtools
#endif //  PICO_YAML_H