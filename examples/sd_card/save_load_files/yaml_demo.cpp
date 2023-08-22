#include <stdio.h>
#include "pico/stdlib.h"
#include <drivers.h>
#include "../../rm_pico_dev/src/Debug/SDCard/File.h"
#include "../../rm_pico_dev/src/Debug/SDCard/Yaml.h"
#include "../../rm_pico_dev/src/Debug/SDCard/TextFile.h"

// #include <nlohmann/json.hpp>

#include <yaml-cpp/yaml.h>
#include <string>

// This needs to be here for the YAML::Load() function to work??
// https://github.com/earlephilhower/arduino-pico/issues/978#issuecomment-1314963917
extern "C" unsigned int __atomic_fetch_add_4(volatile void *ptr, unsigned int val, int memmodel)
{
    (void)memmodel;
    unsigned int tmp = *(unsigned int *)ptr;
    *(unsigned int *)ptr = tmp + val;
    return tmp;
}

int main()
{
    stdio_init_all();
    sleep_ms(1000);

    for (int i = 0; i < 4; i++)
    {
        sleep_ms(1000);
        printf("%d,", 4 - i);
        if (getchar_timeout_us(100) != -1)
            break;
    }
    puts("");

    std::string filename = "test.yaml";
    pico::Drivers *drivers = new pico::Drivers();
    std::cout << "mounting..." << std::endl;
    drivers->sdCard.init();
    drivers->sdCard.mount();
    sleep_ms(100);
    std::cout << "reading file" << std::endl;



    debugtools::File* file = new debugtools::File(filename);
    debugtools::Yaml *yamlFile = new debugtools::Yaml(file);
    bool rez;

    std::cout << "get yaml file" << std::endl;
    YAML::Node node = yamlFile->getNode();
    std::cout << "getYamlFile() worked:" << std::endl;
    for (std::size_t i = 0; i < node["test"].size(); i++)
    {
        std::cout << node["test"][i].as<int>() << "\n";
        node["test"][i] = node["test"][i].as<int>()+11;
    }

    std::cout << "writing bak" << std::endl;
    yamlFile->save();

    debugtools::TextFile *txt = new debugtools::TextFile(file);

    char *raw = txt->getContents();
    std::cout << "raw: "<<raw << std::endl;
    raw[0] = 'a';
    std::cout << "raw2: "<<raw << std::endl;
    txt->save();

    //--
    rez = yamlFile->read();
    std::cout << "get yaml file" << std::endl;
    node = yamlFile->getNode();
    std::cout << "getYamlFile() worked" << std::endl;
    for (std::size_t i = 0; i < node["test"].size(); i++)
    {
        std::cout << node["test"][i].as<int>() << "\n";
    }
    //--

    drivers->sdCard.unmount();
    while (1)
    {
        // printf("doing stuff");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        // printf(".\n");

        // drivers->debug.runNextCommand();
        tight_loop_contents();
    }
}
// */
