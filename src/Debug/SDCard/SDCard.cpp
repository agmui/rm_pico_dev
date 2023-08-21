#include "SDCard.h"
#include "pico/stdlib.h"
#include <iostream>
#include "../CliFunctions.cpp"

namespace debugtools
{
    void SDCard::init()
    {
        time_init(); // TODO: put this in drivers or something
        pSD = sd_get_by_num(0);
    }

    bool SDCard::mount()
    {
        if (pSD->mounted)
            printf("WARNING: sdcard already mounted\n");

        bool rez = mountCard(pSD->pcName);
        if (!rez)
            printf("Error in mountCard()\n");
        return rez;
    }

    bool SDCard::unmount()
    {
        if (!pSD->mounted)
            printf("WARNING: sdcard not mounted\n");

        bool rez = unmountCard(pSD->pcName);
        if (!rez)
            printf("Error in unmountCard()");
        return rez;
    }

} // namespace debugtools
