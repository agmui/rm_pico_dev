#ifndef PICO_MPU6050_H_
#define PICO_MPU6050_H_

#include "ImuInterface.h"

namespace pico::communication::sensors::imu::mpu6050
{
    class MPU6050 : public ImuInterface
    {
    private:
        /* data */
    public:
        MPU6050(Drivers *drivers);
        ~MPU6050();
        void initialize();
        ImuState getImuState();
        periodicIMUUpdate();
    };
    
    
} // namespace pico::communication::sensors::imu::mpu6050



#endif //  PICO_MPU6050_H_