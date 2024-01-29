#include "drivers.h"
#include "BNO055.h"

#define I2C_PORT i2c0

static const int i2c_addr = 0x28; // 0x29//0x68;
namespace pico::communication::sensors::imu::bno055 {
    BNO055::BNO055(Drivers *drivers) : drivers(drivers) {

    }

    bool BNO055::init(float sampleFrequency, float mahonyKp, float mahonyKi) {

        i2c_init(I2C_PORT, 400 * 1000);
        // Init i2c pins on pico
        gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
        gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

        uint8_t chipID = i2cReadRegister(BNO055_CHIP_ID_ADDR);

        uint timeout = 850; //in ms
        if (chipID != 0xA0) {
            while (timeout > 0) {
                printf("Chip ID Not Correct - Check Connection!");
                sleep_ms(1000);
                timeout -= 10;
            }
            imuState = ImuState::IMU_NOT_CONNECTED;
            return false;
        }

        // Use internal oscillator
        i2cWriteRegister(BNO055_SYS_TRIGGER_ADDR, 0x40);

        // Reset all interrupt status bits
        i2cWriteRegister(BNO055_SYS_TRIGGER_ADDR, 0x01);

        // Configure Power Mode to Normal mode
        i2cWriteRegister(BNO055_PWR_MODE_ADDR, 0x00);
        sleep_ms(50);//TODO: test sleep times

        // Default Axis Configuration
        i2cWriteRegister(BNO055_AXIS_MAP_CONFIG_ADDR, 0x24);
        sleep_ms(50);//TODO: test sleep times

        // Default Axis Signs
        i2cWriteRegister(BNO055_AXIS_MAP_SIGN_ADDR, 0x00);

        // Set units to degrees C, Degrees, dps, and m/s^2
        i2cWriteRegister(BNO055_UNIT_SEL_ADDR, 0b0001000);
        sleep_ms(30);

        // Set operation to acceleration only
        i2cWriteRegister(BNO055_OPR_MODE_ADDR, 0x0C);
        sleep_ms(100);

        imuState = ImuState::IMU_NOT_CALIBRATED;
        return true;
    }

    bool BNO055::read() {
        uint8_t data[6];
        memset(data, 0, 6);
        //TODO: read all reg in, all at once

        // Start reading acceleration registers from register 0x08 for 6 bytes
        i2cReadRegisters(BNO055_ACCEL_DATA_X_LSB_ADDR, data, 6);
        raw.accel.x = BIG_ENDIAN_INT16_TO_FLOAT(data);
        raw.accel.y = BIG_ENDIAN_INT16_TO_FLOAT(data + 1);
        raw.accel.z = BIG_ENDIAN_INT16_TO_FLOAT(data + 2);
        memset(data, 0, 6);

        // Magnetometer
        /*
        i2cReadRegisters(BNO055_MAG_DATA_X_LSB_ADDR, data, 6);
        raw.mag.x = BIG_ENDIAN_INT16_TO_FLOAT(data);
        raw.mag.y = BIG_ENDIAN_INT16_TO_FLOAT(data + 1);
        raw.mag.z = BIG_ENDIAN_INT16_TO_FLOAT(data + 2);
        memset(data, 0, 6);
         */

        // gyro data
        i2cReadRegisters(BNO055_GYRO_DATA_X_LSB_ADDR, data, 6);
        raw.gyro.x = BIG_ENDIAN_INT16_TO_FLOAT(data);
        raw.gyro.y = BIG_ENDIAN_INT16_TO_FLOAT(data + 1);
        raw.gyro.z = BIG_ENDIAN_INT16_TO_FLOAT(data + 2);
        memset(data, 0, 6);

        //heading roll pitch
        i2cReadRegisters(BNO055_EULER_H_LSB_ADDR, data, 6);
        raw.yaw = BIG_ENDIAN_INT16_TO_FLOAT(data);
        raw.roll = BIG_ENDIAN_INT16_TO_FLOAT(data + 1);
        raw.pitch = BIG_ENDIAN_INT16_TO_FLOAT(data + 2);
        memset(data, 0, 6);

        /*
        //linear acceleration
        i2cReadRegisters(BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR, data, 6);
        raw. = BIG_ENDIAN_INT16_TO_FLOAT(data);
        raw. = BIG_ENDIAN_INT16_TO_FLOAT(data+1);
        raw. = BIG_ENDIAN_INT16_TO_FLOAT(data+2);
         */

        // temperature
        i2cReadRegisters(BNO055_TEMP_ADDR, data, 6);
        raw.temperature = BIG_ENDIAN_INT16_TO_FLOAT(data);

//        prevIMUDataReceivedTime = //TODO:
        return false;//TODO
    }

    float getTiltAngle() {
        //TODO:
        return 0.0;
    }

    void requestCalibration() {

    }

    void BNO055::getSystemStatus(uint8_t *system_status, uint8_t *self_test_result, uint8_t *system_error) {
        i2cWriteRegister(BNO055_PAGE_ID_ADDR, 0);

        if (system_status != nullptr)
            *system_status = i2cReadRegister(BNO055_SYS_STAT_ADDR);

        if (self_test_result != nullptr)
            *self_test_result = i2cReadRegister(BNO055_SELFTEST_RESULT_ADDR);


        if (system_error != nullptr)
            *system_error = i2cReadRegister(BNO055_SYS_ERR_ADDR);

        sleep_ms(200);
    }

    void BNO055::getCalibration(uint8_t *sys, uint8_t *gyro, uint8_t *accel, uint8_t *mag) {
        uint8_t calData = i2cReadRegister(BNO055_CALIB_STAT_ADDR);
        if (sys != nullptr)
            *sys = (calData >> 6) & 0x03;
        if (gyro != nullptr)
            *gyro = (calData >> 4) & 0x03;
        if (accel != nullptr)
            *accel = (calData >> 2) & 0x03;
        if (mag != nullptr)
            *mag = calData & 0x03;
    }

    void BNO055::getVector(BNO055::vector_type_t vector_type, vector &vector) {
        uint8_t data[6];
        memset(data, 0, 6);
        i2cReadRegisters((bno055_reg_t) vector_type, data, 6);
        switch (vector_type) {
            case VECTOR_MAGNETOMETER:
            case VECTOR_GYROSCOPE:
            case VECTOR_EULER:
                vector.x = convertRawDeg(data[0], raw.gyroOffset.x);
                vector.y = convertRawDeg(data[1], raw.gyroOffset.y);
                vector.z = convertRawDeg(data[2], raw.gyroOffset.z);
                break;
            case VECTOR_ACCELEROMETER:
            case VECTOR_LINEARACCEL:
            case VECTOR_GRAVITY:
                vector.x = convertRawLin(data[0], raw.accelOffset.x);
                vector.y = convertRawLin(data[1], raw.accelOffset.y);
                vector.z = convertRawLin(data[2], raw.accelOffset.z);
                break;
        }
    }

    void BNO055::getQuaternions(int16_t &x, int16_t &y, int16_t &z, int16_t &w){
        uint8_t data[8];
        memset(data, 0, 8);

//        int16_t x, y, z, w;
//        x = y = z = w = 0;

        /* Read quat data (8 bytes) */
        i2cReadRegisters(BNO055_QUATERNION_DATA_W_LSB_ADDR, data, 8);

        w = BIG_ENDIAN_INT16_TO_FLOAT(data);
        x = BIG_ENDIAN_INT16_TO_FLOAT(data+1);
        y = BIG_ENDIAN_INT16_TO_FLOAT(data+2);
        z = BIG_ENDIAN_INT16_TO_FLOAT(data+3);
//      w = (((uint16_t)data[1]) << 8) | ((uint16_t)data[0]);
//      x = (((uint16_t)data[3]) << 8) | ((uint16_t)data[2]);
//      y = (((uint16_t)data[5]) << 8) | ((uint16_t)data[4]);
//      z = (((uint16_t)data[7]) << 8) | ((uint16_t)data[6]);

        /*!
         * Assign to Quaternion
         * See
         * https://cdn-shop.adafruit.com/datasheets/BST_BNO055_DS000_12.pdf
         * 3.6.5.5 Orientation (Quaternion)
         */
        const double scale = (1.0 / (1 << 14));
        w *= scale;
        x *= scale;
        y *= scale;
        z *= scale;
//        quaternion = {scale * w, scale * x, scale * y, scale * z};
    }

    void BNO055::i2cWriteRegister(bno055_reg_t reg, uint8_t value) {
        uint8_t data[2] = {static_cast<uint8_t>(reg), value};
        i2c_write_blocking(I2C_PORT, i2c_addr, data, 2, true); // true to keep master control of bus
    }

    uint8_t BNO055::i2cReadRegister(bno055_reg_t reg) {
        uint8_t data;
        i2c_write_blocking(I2C_PORT, i2c_addr, (const uint8_t *) reg, 1, true); // true to keep master control of bus
        i2c_read_blocking(I2C_PORT, i2c_addr, &data, 1, false); // False - finished with bus
        return data;
    }

    void BNO055::i2cReadRegisters(bno055_reg_t reg, uint8_t *data, size_t len) {
        i2c_write_blocking(I2C_PORT, i2c_addr, (const uint8_t *) reg, 1, true); // true to keep master control of bus
        i2c_read_blocking(I2C_PORT, i2c_addr, data, len, false); // False - finished with bus
    }

    void BNO055::addValidationErrors() {


    }

    void BNO055::defaultProcessRawMpu6500Data(const uint8_t (&rxBuff)[28], vector &accel, vector &gyro) {

    }


} // namespace BNO055
