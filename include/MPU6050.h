#ifndef PICO_MPU6050_H_
#define PICO_MPU6050_H_

#include "../src/ImuInterface.h"
#include "drivers.h"

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
        inline const char *getName() const override;

        /**
         * Returns the linear acceleration in the x direction, in
         * \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         */
        inline float getAx() override;

        /**
         * Returns the linear acceleration in the y direction, in
         * \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         */
        inline float getAy() override;

        /**
         * Returns the linear acceleration in the z direction, in
         * \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         */
        inline float getAz() override;

        /**
         * Returns the gyroscope reading (rotational speed) in the x direction, in
         * \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         */
        inline float getGx() override;

        /**
         * Returns the gyroscope reading (rotational speed) in the y direction, in
         * \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         */
        inline float getGy() override;

        /**
         * Returns the gyroscope reading (rotational speed) in the z direction, in
         * \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         */
        inline float getGz() override;

        /**
         * Returns the temperature of the imu in degrees C.
         */
        inline float getTemp() override;

        /**
         * Returns yaw angle. in degrees.
         */
        inline float getYaw() override;

        /**
         * Returns pitch angle in degrees.
         */
        inline float getPitch() override;

        /**
         * Returns roll angle in degrees.
         */
        inline float getRoll() override;
    };

} // namespace pico::communication::sensors::imu::mpu6050

#endif //  PICO_MPU6050_H_