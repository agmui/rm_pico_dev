
#include "pico/stdlib.h"
#include "Yaml.h"
#include "File.h"
#include <iostream>

namespace debugtools
{
    // Yaml::Yaml(std::string filename){
    //     readFile();
    // }
    //todo check if name is updated
    bool Yaml::cast(char *buf)
    {
        node = YAML::Load(buf);
        return false;//todo
    }

    bool Yaml::save(){
        YAML::Emitter out;
        out << node;
        bool result = overWrite(out.c_str()); // todo add cap to write to size?
        return result;
    }
} // namespace debugtools
