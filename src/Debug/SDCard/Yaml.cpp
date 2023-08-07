#include "Yaml.h"
#include "File.h"

namespace debugtools
{
    Yaml::Yaml(File *file)
    {
        // char buf[256];
        // file->getRawText(buf);
        // node = YAML::Load(buf);

        node = YAML::Load("[1]");
    }
} // namespace debugtools
