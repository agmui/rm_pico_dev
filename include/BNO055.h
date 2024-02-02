#ifndef PICO_BNO055_H_
#define PICO_BNO055_H_

/*
 * Copyright (c) 2020-2022 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of Taproot.
 *
 * Taproot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Taproot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Taproot.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include "hardware/i2c.h"
#include "../src/ImuInterface.h"

#include <cstdint>

//#include "tap/algorithms/MahonyAHRS.h"
//#include "tap/architecture/timeout.hpp"
//#include "tap/communication/sensors/imu/imu_interface.hpp"
//#include "tap/communication/sensors/imu_heater/imu_heater.hpp"
//#include "tap/util_macros.hpp"

//#include "modm/math/geometry.hpp"
//#include "modm/processing/protothread.hpp"

#define LITTLE_ENDIAN_INT16_TO_FLOAT(buff) \
     (static_cast<float>(static_cast<int16_t>((*(buff) << 8) | *(buff + 1))))

//#define BIG_ENDIAN_INT8_TO_DOUBLE(buffer, i) (static_cast<float>(buffer[i*2+1]<<8|buffer[(i*2)]))

#define BIG_ENDIAN_INT16_TO_FLOAT(buff) \
     (static_cast<float>(static_cast<int16_t>((*(buff+1) << 8) | *(buff))))

namespace pico {
    class Drivers;
}

namespace pico::communication::sensors::imu::bno055 {

    /** A structure to represent 3D vectors **/
    //TODO: get a more official class
    typedef struct {
        float x;
        float y;
        float z;
    } vector;

    /**
     * A class specifically designed for interfacing with the RoboMaster type A board Mpu6500.
     *
     * To use this class, call Remote::init() to properly initialize and calibrate
     * the MPU6500. Next, call Remote::read() to read acceleration, gyro, and temperature
     * values from the imu. Use the getter methods to access imu information.
     *
     * @note if you are shaking the imu while it is initializing, the offsets will likely
     *      be calibrated poorly and unexpectedly bad results may occur.
     */
    class BNO055 : public ImuInterface {
    public:

        /** BNO055 Registers **/
        //TODO: maybe make a reg.h file with only #defines
        typedef enum {
            /* Page id register definition */
            BNO055_PAGE_ID_ADDR = 0X07,

            /* PAGE0 REGISTER DEFINITION START*/
            BNO055_CHIP_ID_ADDR = 0x00,
            BNO055_ACCEL_REV_ID_ADDR = 0x01,
            BNO055_MAG_REV_ID_ADDR = 0x02,
            BNO055_GYRO_REV_ID_ADDR = 0x03,
            BNO055_SW_REV_ID_LSB_ADDR = 0x04,
            BNO055_SW_REV_ID_MSB_ADDR = 0x05,
            BNO055_BL_REV_ID_ADDR = 0X06,

            /* Accel data register */
            BNO055_ACCEL_DATA_X_LSB_ADDR = 0X08,
            BNO055_ACCEL_DATA_X_MSB_ADDR = 0X09,
            BNO055_ACCEL_DATA_Y_LSB_ADDR = 0X0A,
            BNO055_ACCEL_DATA_Y_MSB_ADDR = 0X0B,
            BNO055_ACCEL_DATA_Z_LSB_ADDR = 0X0C,
            BNO055_ACCEL_DATA_Z_MSB_ADDR = 0X0D,

            /* Mag data register */
            BNO055_MAG_DATA_X_LSB_ADDR = 0X0E,
            BNO055_MAG_DATA_X_MSB_ADDR = 0X0F,
            BNO055_MAG_DATA_Y_LSB_ADDR = 0X10,
            BNO055_MAG_DATA_Y_MSB_ADDR = 0X11,
            BNO055_MAG_DATA_Z_LSB_ADDR = 0X12,
            BNO055_MAG_DATA_Z_MSB_ADDR = 0X13,

            /* Gyro data registers */
            BNO055_GYRO_DATA_X_LSB_ADDR = 0X14,
            BNO055_GYRO_DATA_X_MSB_ADDR = 0X15,
            BNO055_GYRO_DATA_Y_LSB_ADDR = 0X16,
            BNO055_GYRO_DATA_Y_MSB_ADDR = 0X17,
            BNO055_GYRO_DATA_Z_LSB_ADDR = 0X18,
            BNO055_GYRO_DATA_Z_MSB_ADDR = 0X19,

            /* Euler data registers */
            BNO055_EULER_H_LSB_ADDR = 0X1A,
            BNO055_EULER_H_MSB_ADDR = 0X1B,
            BNO055_EULER_R_LSB_ADDR = 0X1C,
            BNO055_EULER_R_MSB_ADDR = 0X1D,
            BNO055_EULER_P_LSB_ADDR = 0X1E,
            BNO055_EULER_P_MSB_ADDR = 0X1F,

            /* Quaternion data registers */
            BNO055_QUATERNION_DATA_W_LSB_ADDR = 0X20,
            BNO055_QUATERNION_DATA_W_MSB_ADDR = 0X21,
            BNO055_QUATERNION_DATA_X_LSB_ADDR = 0X22,
            BNO055_QUATERNION_DATA_X_MSB_ADDR = 0X23,
            BNO055_QUATERNION_DATA_Y_LSB_ADDR = 0X24,
            BNO055_QUATERNION_DATA_Y_MSB_ADDR = 0X25,
            BNO055_QUATERNION_DATA_Z_LSB_ADDR = 0X26,
            BNO055_QUATERNION_DATA_Z_MSB_ADDR = 0X27,

            /* Linear acceleration data registers */
            BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR = 0X28,
            BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR = 0X29,
            BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR = 0X2A,
            BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR = 0X2B,
            BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR = 0X2C,
            BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR = 0X2D,

            /* Gravity data registers */
            BNO055_GRAVITY_DATA_X_LSB_ADDR = 0X2E,
            BNO055_GRAVITY_DATA_X_MSB_ADDR = 0X2F,
            BNO055_GRAVITY_DATA_Y_LSB_ADDR = 0X30,
            BNO055_GRAVITY_DATA_Y_MSB_ADDR = 0X31,
            BNO055_GRAVITY_DATA_Z_LSB_ADDR = 0X32,
            BNO055_GRAVITY_DATA_Z_MSB_ADDR = 0X33,

            /* Temperature data register */
            BNO055_TEMP_ADDR = 0X34,

            /* Status registers */
            BNO055_CALIB_STAT_ADDR = 0X35,
            BNO055_SELFTEST_RESULT_ADDR = 0X36,
            BNO055_INTR_STAT_ADDR = 0X37,

            BNO055_SYS_CLK_STAT_ADDR = 0X38,
            BNO055_SYS_STAT_ADDR = 0X39,
            BNO055_SYS_ERR_ADDR = 0X3A,

            /* Unit selection register */
            BNO055_UNIT_SEL_ADDR = 0X3B,

            /* Mode registers */
            BNO055_OPR_MODE_ADDR = 0X3D,
            BNO055_PWR_MODE_ADDR = 0X3E,

            BNO055_SYS_TRIGGER_ADDR = 0X3F,
            BNO055_TEMP_SOURCE_ADDR = 0X40,

            /* Axis remap registers */
            BNO055_AXIS_MAP_CONFIG_ADDR = 0X41,
            BNO055_AXIS_MAP_SIGN_ADDR = 0X42,

            /* SIC registers */
            BNO055_SIC_MATRIX_0_LSB_ADDR = 0X43,
            BNO055_SIC_MATRIX_0_MSB_ADDR = 0X44,
            BNO055_SIC_MATRIX_1_LSB_ADDR = 0X45,
            BNO055_SIC_MATRIX_1_MSB_ADDR = 0X46,
            BNO055_SIC_MATRIX_2_LSB_ADDR = 0X47,
            BNO055_SIC_MATRIX_2_MSB_ADDR = 0X48,
            BNO055_SIC_MATRIX_3_LSB_ADDR = 0X49,
            BNO055_SIC_MATRIX_3_MSB_ADDR = 0X4A,
            BNO055_SIC_MATRIX_4_LSB_ADDR = 0X4B,
            BNO055_SIC_MATRIX_4_MSB_ADDR = 0X4C,
            BNO055_SIC_MATRIX_5_LSB_ADDR = 0X4D,
            BNO055_SIC_MATRIX_5_MSB_ADDR = 0X4E,
            BNO055_SIC_MATRIX_6_LSB_ADDR = 0X4F,
            BNO055_SIC_MATRIX_6_MSB_ADDR = 0X50,
            BNO055_SIC_MATRIX_7_LSB_ADDR = 0X51,
            BNO055_SIC_MATRIX_7_MSB_ADDR = 0X52,
            BNO055_SIC_MATRIX_8_LSB_ADDR = 0X53,
            BNO055_SIC_MATRIX_8_MSB_ADDR = 0X54,

            /* Accelerometer Offset registers */
            ACCEL_OFFSET_X_LSB_ADDR = 0X55,
            ACCEL_OFFSET_X_MSB_ADDR = 0X56,
            ACCEL_OFFSET_Y_LSB_ADDR = 0X57,
            ACCEL_OFFSET_Y_MSB_ADDR = 0X58,
            ACCEL_OFFSET_Z_LSB_ADDR = 0X59,
            ACCEL_OFFSET_Z_MSB_ADDR = 0X5A,

            /* Magnetometer Offset registers */
            MAG_OFFSET_X_LSB_ADDR = 0X5B,
            MAG_OFFSET_X_MSB_ADDR = 0X5C,
            MAG_OFFSET_Y_LSB_ADDR = 0X5D,
            MAG_OFFSET_Y_MSB_ADDR = 0X5E,
            MAG_OFFSET_Z_LSB_ADDR = 0X5F,
            MAG_OFFSET_Z_MSB_ADDR = 0X60,

            /* Gyroscope Offset register s*/
            GYRO_OFFSET_X_LSB_ADDR = 0X61,
            GYRO_OFFSET_X_MSB_ADDR = 0X62,
            GYRO_OFFSET_Y_LSB_ADDR = 0X63,
            GYRO_OFFSET_Y_MSB_ADDR = 0X64,
            GYRO_OFFSET_Z_LSB_ADDR = 0X65,
            GYRO_OFFSET_Z_MSB_ADDR = 0X66,

            /* Radius registers */
            ACCEL_RADIUS_LSB_ADDR = 0X67,
            ACCEL_RADIUS_MSB_ADDR = 0X68,
            MAG_RADIUS_LSB_ADDR = 0X69,
            MAG_RADIUS_MSB_ADDR = 0X6A
        } bno055_reg_t;

        /** Vector Mappings **/
        typedef enum {
            VECTOR_ACCELEROMETER = BNO055_ACCEL_DATA_X_LSB_ADDR,
            VECTOR_MAGNETOMETER = BNO055_MAG_DATA_X_LSB_ADDR,
            VECTOR_GYROSCOPE = BNO055_GYRO_DATA_X_LSB_ADDR,
            VECTOR_EULER = BNO055_EULER_H_LSB_ADDR,
            VECTOR_LINEARACCEL = BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR,
            VECTOR_GRAVITY = BNO055_GRAVITY_DATA_X_LSB_ADDR
        } vector_type_t;


        /**
         * The number of bytes read to read acceleration, gyro, magnetometer and temperature.
         */
        static constexpr uint8_t ACC_MAG_GYRO_TEMPERATURE_BUFF_RX_SIZE = 28;

        /**
         * Storage for the raw data we receive from the BNO055, as well as offsets
         * that are used each time we receive data.
         */
        struct RawData {
            /**
             * Raw acceleration data.
             */
            vector accel{};
            /**
             * Raw gyroscope data.
             */
             vector gyro{};

            /**
             * Raw magnetometer data.
             */
            // vector mag{};

            /**
             * Raw orientation values
             */
            float yaw;
            float roll;
            float pitch;

            /**
             * Raw temperature.
             */
            uint16_t temperature = 0;

            /**
             * Acceleration offset set in init.
             */
            vector accelOffset{0,0,0};
            /**
             * Gyroscope offset calculated in init.
             */
            vector gyroOffset{0,0,0};
        };

        BNO055(Drivers *drivers);

        //    DISALLOW_COPY_AND_ASSIGN(Mpu6500)
        ~BNO055() = default;

        /**
         * Initialize the imu and the SPI line. Uses SPI1, which is internal to the
         * type A board.
         *
         * @note this function can block for approximately 12 seconds.
         */
        bool init();

        /**
         * Read data from the imu.
         *
         * @note this function blocks
         *
         * @return `true` if the function is not done, `false` otherwise
         */
        bool read();

        /**
         * Returns the state of the IMU. Can be not connected, connected but not calibrated, calibrating
         * or calibrated. When not connected, IMU data is undefiend. When not calibrated, IMU data is
         * valid but the computed yaw angle data will drift. When calibrating, the IMU data is invalid.
         * When calibrated, the IMU data is valid and assuming proper calibration the IMU data should
         * not drift.
         *
         * To be safe, whenever you call functions that return IMU (acceleration, gyroscope,
         * temperature, and angle) data, call this function to ensure the data you are about to receive
         * is not undefined.
         */
        inline ImuState getImuState() const { return imuState; }

        //    virtual inline const char *getName() const { return "BNO055"; }
        inline const char *getName() override { return "BNO055"; }

        /**
         * If the imu is not initialized, logs an error and returns 0.
         * Otherwise, returns the value passed in.
         */
        inline float validateReading(float reading) {
            if (imuState == ImuState::IMU_CALIBRATED) {
                return reading;
            } else if (imuState == ImuState::IMU_NOT_CALIBRATED) {
                errorState |= 1 << static_cast<uint8_t>(ImuState::IMU_NOT_CALIBRATED);
                return reading;
            } else if (imuState == ImuState::IMU_CALIBRATING) {
                errorState |= 1 << static_cast<uint8_t>(ImuState::IMU_CALIBRATING);
                return 0.0f;
            } else {
                errorState |= 1 << static_cast<uint8_t>(ImuState::IMU_NOT_CONNECTED);
                return 0.0f;
            }
        }

        /**
         * Returns the acceleration reading in the x direction, in
         * \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         */
        inline float getAx() {
//         return validateReading(
//             static_cast<float>(raw.accel.x - raw.accelOffset.x) * ACCELERATION_GRAVITY /
//             ACCELERATION_SENSITIVITY);
            return convertRawLin(raw.accel.z);
        }

        /**
         * Returns the acceleration reading in the y direction, in
         * \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         */
        inline float getAy() {
//         return validateReading(
//             static_cast<float>(raw.accel.y - raw.accelOffset.y) * ACCELERATION_GRAVITY /
//             ACCELERATION_SENSITIVITY);
            return convertRawLin(raw.accel.z);
        }

        /**
         * Returns the acceleration reading in the z direction, in
         * \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         */
        inline float getAz() {
//         return validateReading(
//             static_cast<float>(raw.accel.z - raw.accelOffset.z) * ACCELERATION_GRAVITY /
//             ACCELERATION_SENSITIVITY);
            return convertRawLin(raw.accel.z);
        }

        /**
         * Returns the gyroscope reading in the x direction, in
         * \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         */
        inline float getGx() {
//         return validateReading(
//             static_cast<float>(raw.gyro.x - raw.gyroOffset.x) / LSB_D_PER_S_TO_D_PER_S);
            return convertRawDeg(raw.gyro.x);
        }

        /**
         * Returns the gyroscope reading in the y direction, in
         * \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         */
        inline float getGy() {
//         return validateReading(
//             static_cast<float>(raw.gyro.y - raw.gyroOffset.y) / LSB_D_PER_S_TO_D_PER_S);
            return convertRawDeg(raw.gyro.y);
        }

        /**
         * Returns the gyroscope reading in the z direction, in
         * \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         */
        inline float getGz() {
//         return validateReading(
//             static_cast<float>(raw.gyro.z - raw.gyroOffset.z) / LSB_D_PER_S_TO_D_PER_S);
            return convertRawDeg(raw.gyro.z);
        }

        /**
         * Returns the temperature of the imu in degrees C.
         *
         */
        inline float getTemp() {
            return validateReading(raw.temperature);
        }

        /**
         * Returns yaw angle. in degrees.
         */
        inline float getYaw() { return validateReading(raw.yaw); };

        /**
         * Returns pitch angle in degrees.
         */
        inline float getPitch() { return validateReading(raw.pitch); };

        /**
         * Returns roll angle in degrees.
         */
        inline float getRoll() { return validateReading(raw.roll); };

        //TODO: update value
        inline uint32_t getPrevIMUDataReceivedTime() const { return prevIMUDataReceivedTime; }

        /**
         * Returns the angle difference between the normal vector of the plane that the
         * type A board lies on and of the angle directly upward.
         */
        float getTiltAngle();

        /**
         * Uninitializes the bno055 and enters calibration mode.
         */
        void requestCalibration();


        /*!
         *   @brief  Gets the latest system status info
         *   @param  system_status
         *           system status info
         *          0 = Idle
         *          1 = System Error
         *          2 = Initializing Peripherals
         *          3 = System Iniitalization
         *          4 = Executing Self-Test
         *          5 = Sensor fusio algorithm running
         *          6 = System running without fusion algorithms
         *   @param  self_test_result
         *           self test result
         *
         *           1 = test passed, 0 = test failed
         *
         *           Bit 0 = Accelerometer self test
         *           Bit 1 = Magnetometer self test
         *           Bit 2 = Gyroscope self test
         *           Bit 3 = MCU self test
         *
         *           0x0F = all good!
         *   @param  system_error
         *           system error info
         *           0 = No error
         *           1 = Peripheral initialization error
         *           2 = System initialization error
         *           3 = Self test result failed
         *           4 = Register map value out of range
         *           5 = Register map address out of range
         *           6 = Register map write error
         *           7 = BNO low power mode not available for selected operation mode
         *           8 = Accelerometer power mode not available
         *           9 = Fusion algorithm configuration error
         *           A = Sensor configuration error
         */
        void getSystemStatus(uint8_t *system_status,
                             uint8_t *self_test_result,
                             uint8_t *system_error);

        /*!
         *  @brief  Gets current calibration state.  Each value should be a uint8_t
         *          pointer and it will be set to 0 if not calibrated and 3 if
         *          fully calibrated.
         *          See section 34.3.54
         *  @param  sys
         *          Current system calibration status, depends on status of all sensors,
         * read-only
         *  @param  gyro
         *          Current calibration status of Gyroscope, read-only
         *  @param  accel
         *          Current calibration status of Accelerometer, read-only
         *  @param  mag
         *          Current calibration status of Magnetometer, read-only
         */
        void getCalibration(uint8_t *sys, uint8_t *gyro,
                            uint8_t *accel, uint8_t *mag);


        /*!
         *  @brief   Gets a vector reading from the specified source
         *  @param   vector_type
         *           possible vector type values
         *           [VECTOR_ACCELEROMETER
         *            VECTOR_MAGNETOMETER
         *            VECTOR_GYROSCOPE
         *            VECTOR_EULER
         *            VECTOR_LINEARACCEL
         *            VECTOR_GRAVITY]
         *  @param  vector result from specified source
         */
        void getVector(vector_type_t vector_type, vector &vector);

        /*!
         *  @brief  Gets a quaternion reading from the specified source
         *
         * @param x
         * @param y
         * @param z
         * @param w
         */
        void getQuaternions(int16_t &x, int16_t &y, int16_t &z, int16_t &w);

        /**
         * Use for converting from gyro values we receive to more conventional degrees / second.
         *     1dps = 16 LSB
         */
        static constexpr float LSB_D_PER_S_TO_D_PER_S = 16.0;//.384f;TODO: find out why there is .384f

    private:
        static constexpr float ACCELERATION_GRAVITY = 9.80665f;

        /**
         * Use to convert the raw acceleration into more conventional degrees / second^2
         */
        static constexpr float ACCELERATION_SENSITIVITY = 100.0;

        /**
         * The number of samples we take while calibrating in order to determine the mpu offsets.
         */
        static constexpr float BNO055_OFFSET_SAMPLES = 1000;

        /**
         * The time to read the registers in nonblocking mode, in microseconds.
         */
        static constexpr int NONBLOCKING_TIME_TO_READ_REG = 450;

        /**
         * Time in ms to wait for the IMU heat to stabilize upon initialization.
         */
        static constexpr uint32_t MAX_WAIT_FOR_IMU_TEMPERATURE_STABALIZE = 10'000;

        /**
         * Time in ms to wait after IMU heat has reached stable point upon initialization.
         */
        static constexpr uint32_t WAIT_TIME_AFTER_CALIBRATION = 10'000;

        /**
         * Bit appended or removed from a register while reading/writing.
         */
        static constexpr uint8_t BNO055_READ_BIT = 0x80;

        Drivers *drivers;

        int delayBtwnCalcAndReadReg = 2000 - NONBLOCKING_TIME_TO_READ_REG;

        ImuState imuState = ImuState::IMU_NOT_CONNECTED;

        //    tap::arch::MicroTimeout readRegistersTimeout;
        //    uint8_t tx = 0;  ///< Byte used for reading data in the read protothread
        //    uint8_t rx = 0;  ///< Byte used for reading data in the read protothread

        RawData raw;

        float tiltAngle = 0.0f;
        bool tiltAngleCalculated = false;

        uint8_t txBuff[ACC_MAG_GYRO_TEMPERATURE_BUFF_RX_SIZE] = {0};

        uint8_t rxBuff[ACC_MAG_GYRO_TEMPERATURE_BUFF_RX_SIZE] = {0};

//        int calibrationSample = 0;

        uint8_t errorState = 0;//TODO:

        uint32_t prevIMUDataReceivedTime = 0;

        // Functions for interacting with hardware directly.

        /**
         * @brief Convert between raw read bytes to \f$\frac{\mbox{degrees}}{\mbox{second}}\f$.
         *
         * See
         * https://cdn-shop.adafruit.com/datasheets/BST_BNO055_DS000_12.pdf
         * 3.6.5.3 Angular Velocity
         * @param rawDeg
         * @param offset
         * @return
         */
        float convertRawDeg(uint8_t rawDeg) {
            return validateReading(
                    static_cast<float>(rawDeg) / LSB_D_PER_S_TO_D_PER_S);
        }

        /**
         * @brief Convert from raw read bytes to \f$\frac{\mbox{m}}{\mbox{second}^2}\f$.
         * See
         * https://cdn-shop.adafruit.com/datasheets/BST_BNO055_DS000_12.pdf
         * 3.6.5.6 Linear Acceleration
         * @param rawDeg
         * @param offset
         * @return
         */
        float convertRawLin(uint8_t rawLin) {
//            return validateReading(
//                    static_cast<float>(rawLin - offset) * ACCELERATION_GRAVITY /
//                    ACCELERATION_SENSITIVITY);
            return validateReading(static_cast<float>(rawLin)  / ACCELERATION_SENSITIVITY);
        }

        /**
         * Write to a given register.
         */
        void i2cWriteRegister(bno055_reg_t reg, uint8_t value);

        /**
         * Read from a given register.
         */
        uint8_t i2cReadRegister(bno055_reg_t reg);

        /**
         * Read from several registers.
         * regAddr is the first address read, and it reads len number of addresses
         * from that point.
         */
        void i2cReadRegisters(bno055_reg_t reg, uint8_t *data, size_t len);

//        /**
//         * Add any errors to the error handler that have came up due to calls to validateReading.
//         */
//        void addValidationErrors();

    };
} // namespace pico::communication::sensors::imu::bno055


#endif //  PICO_BNO055_H_