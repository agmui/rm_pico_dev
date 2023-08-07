
#include <stdio.h>
#include "pico/stdlib.h"
#include <drivers.h>
#include "rm_pico_dev/src/Debug/SDCard/File.h"

// #include "rm_pico_dev/lib/json/include/nlohmann/json.hpp"
#include <nlohmann/json.hpp>

// #include "rm_pico_dev/lib/tiny-json/tiny-json.h"
// #include "rm_pico_dev/lib/json-maker/src/include/json-maker/json-maker.h"
#include <yaml-cpp/yaml.h>

// This needs to be here for the YAML::Load() function to work??
//https://github.com/earlephilhower/arduino-pico/issues/978#issuecomment-1314963917
extern "C" unsigned int __atomic_fetch_add_4(volatile void* ptr, unsigned int val, int memmodel) {
	(void)memmodel;
	unsigned int tmp = *(unsigned int*)ptr;
	*(unsigned int*)ptr = tmp + val;
	return tmp;
}
using json = nlohmann::json;

int main()
{
    stdio_init_all();
    sleep_ms(1000);


    for (int i = 0; i < 4; i++)
    {
        sleep_ms(1000);
        printf("%d,", 4 - i);
        if(getchar_timeout_us(100)!=-1) break;
    }
    puts("");

    YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
    for (std::size_t i=0;i<primes.size();i++) {
    std::cout << primes[i].as<int>() << "\n";
    }

    json ex1 = json::parse(R"(
  {
    "pi": 3.141,
    "happy": true
  }
)");
    std::cout << ex1.dump() << std::endl;

    /*
    pico::Drivers *drivers = new pico::Drivers();

    std::cout << "mounting..." << std::endl;
    drivers->sdCard.init();
    drivers->sdCard.mount();
    sleep_ms(100);
    std::cout << "reading file" << std::endl;
    debugtools::File* file = drivers->sdCard.open("test.yaml");
    std::cout << "pass into yaml class" << std::endl;
    debugtools::Yaml* yamlFile = new debugtools::Yaml(file);
    std::cout << "get yaml file" << std::endl;
    YAML::Node node = yamlFile->getYamlFile();
    std::cout << node["test"].as<std::string>() << std::endl;
*/


    while (1)
    {
        printf("doing stuff");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".\n");

        // drivers->debug.runNextCommand();
        tight_loop_contents();

    }
}
// */