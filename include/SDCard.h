#ifndef PICO_SDCARD_H__
#define PICO_SDCARD_H__

namespace pico
{
    class Drivers;
}

namespace debugtools
{
    class SDCard
    {
    private:
        pico::Drivers *drivers;

    public:
        SDCard(pico::Drivers *drivers) : drivers(drivers) {}
        ~SDCard();
    };
} // namespace debugtools

#endif //  PICO_SDCARD_H_