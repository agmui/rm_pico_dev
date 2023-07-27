#ifndef PICO_DEBUG_H_
#define PICO_DEBUG_H_

namespace pico
{
    class Drivers;
}


namespace debugtools
{
    class Debug
    {
    private:
        pico::Drivers *drivers;
    public:
        Debug(pico::Drivers *drivers) : drivers(drivers) {}
        ~Debug();
    };
    
} // namespace debugTools


#endif // PICO_DEBUG_H_