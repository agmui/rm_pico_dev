#ifndef PICO_MPU6050_H_
#define PICO_MPU6050_H_

#include "../src/ImuInterface.h"

namespace pico
{
    class Drivers;
}

namespace pico::communication::sensors::imu::mpu6050
{
    class MPU6050 : public ImuInterface
    {
    private:
        Drivers *drivers;

    public:
        MPU6050(Drivers *drivers) : drivers(drivers) {}
        ~MPU6050();
        void initialize();
        ImuState getImuState();
        void periodicIMUUpdate();
        inline const char *getName() { return "mpu6050"; }

        /**
         * Returns the linear acceleration in the x direction, in
         * \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         */
        inline float getAx() { return 0; } // TODO:

        /**
         * Returns the linear acceleration in the y direction, in
         * \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         */
        inline float getAy() { return 0; } // TODO:

        /**
         * Returns the linear acceleration in the z direction, in
         * \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         */
        inline float getAz() { return 0; } // TODO:

        /**
         * Returns the gyroscope reading (rotational speed) in the x direction, in
         * \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         */
        inline float getGx() { return 0; } // TODO:

        /**
         * Returns the gyroscope reading (rotational speed) in the y direction, in
         * \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         */
        inline float getGy() { return 0; } // TODO:

        /**
         * Returns the gyroscope reading (rotational speed) in the z direction, in
         * \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         */
        inline float getGz() { return 0; } // TODO:

        /**
         * Returns the temperature of the imu in degrees C.
         */
        inline float getTemp() { return 0; } // TODO:

        /**
         * Returns yaw angle. in degrees.
         */
        inline float getYaw() { return 0; } // TODO:

        /**
         * Returns pitch angle in degrees.
         */
        inline float getPitch() { return 0; } // TODO:

        /**
         * Returns roll angle in degrees.
         */
        inline float getRoll() { return 0; } // TODO:
    };

} // namespace pico::communication::sensors::imu::mpu6050

#endif //  PICO_MPU6050_H_