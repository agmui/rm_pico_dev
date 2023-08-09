
#include "pico/stdlib.h"
#include "Yaml.h"
#include "File.h"
#include <iostream>

namespace debugtools
{
    bool Yaml::cast(char *buf)
    {
        node = YAML::Load(buf);
        return true; // TODO:
    }

    bool Yaml::save()
    {
        YAML::Emitter out;
        out << node;
        bool result = file->overWrite(out.c_str());
        return result;
    }
} // namespace debugtools
