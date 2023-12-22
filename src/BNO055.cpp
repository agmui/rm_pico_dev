#include "drivers.h"
#include "BNO055.h"

#define I2C_PORT i2c0

static const int i2c_addr = 0x28; // 0x29//0x68;
namespace pico::communication::sensors::imu::bno055 {
    bool BNO055::init(float sampleFrequency, float mahonyKp, float mahonyKi) {

        i2c_init(I2C_PORT, 400 * 1000);
        gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
        gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

//        uint8_t chipID[1];

//        uint8_t reg = 0x00;
//        i2c_write_blocking(I2C_PORT, i2c_addr, &reg, 1, true);
//        i2c_read_blocking(I2C_PORT, i2c_addr, chipID, 1, false);
        uint8_t chipID = spiReadByte(BNO055_CHIP_ID_ADDR);

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
        uint8_t data[2];
        data[0] = BNO055_SYS_TRIGGER_ADDR;
        data[1] = BNO055_TEMP_SOURCE_ADDR;
        i2c_write_blocking(I2C_PORT, i2c_addr, data, 2, true);

        // Reset all interrupt status bits
        data[0] = BNO055_SYS_TRIGGER_ADDR;
        data[1] = BNO055_ACCEL_REV_ID_ADDR;
        i2c_write_blocking(I2C_PORT, i2c_addr, data, 2, true);

        // Configure Power Mode
        data[0] = BNO055_PWR_MODE_ADDR;
        data[1] = 0x00;
        i2c_write_blocking(I2C_PORT, i2c_addr, data, 2, true);
        sleep_ms(50);//TODO: remove all sleeps

        // Defaul Axis Configuration
        data[0] = BNO055_AXIS_MAP_CONFIG_ADDR;
        data[1] = BNO055_QUATERNION_DATA_Y_LSB_ADDR;
        i2c_write_blocking(I2C_PORT, i2c_addr, data, 2, true);

        // Default Axis Signs
        data[0] = BNO055_AXIS_MAP_SIGN_ADDR;
        data[1] = 0x00;
        i2c_write_blocking(I2C_PORT, i2c_addr, data, 2, true);

        // Set units to m/s^2
        data[0] = BNO055_UNIT_SEL_ADDR;
        data[1] = 0b0001000;
        i2c_write_blocking(I2C_PORT, i2c_addr, data, 2, true);
        sleep_ms(30);

        // Set operation to acceleration only
        data[0] = BNO055_OPR_MODE_ADDR;
        data[1] = 0x0C;
        i2c_write_blocking(I2C_PORT, i2c_addr, data, 2, true);
        sleep_ms(100);

        imuState = ImuState::IMU_NOT_CALIBRATED;
        return true;
    }

    void BNO055::periodicIMUUpdate() {
        //TODO:
    }

    bool read(){
        //TODO:

    }

    float getTiltAngle(){
        //TODO:
    }

    void requestCalibration(){

    }
    void BNO055::getSystemStatus(uint8_t *system_status, uint8_t *self_test_result, uint8_t *system_error) {
        spiWriteRegister(BNO055_PAGE_ID_ADDR, 1);

        if (system_status != 0)
            *system_status = spiReadByte(BNO055_SYS_STAT_ADDR);

        if (self_test_result != 0)
            *self_test_result = spiReadByte(BNO055_SELFTEST_RESULT_ADDR);


        if (system_error != 0)
            *system_error = spiReadByte(BNO055_SYS_ERR_ADDR);

        sleep_ms(200);
    }

    void BNO055::getCalibration(uint8_t *sys, uint8_t *gyro, uint8_t *accel, uint8_t *mag) {
        uint8_t calData = spiReadByte(BNO055_CALIB_STAT_ADDR);
        if (sys != NULL) {
            *sys = (calData >> 6) & 0x03;
        }
        if (gyro != NULL) {
            *gyro = (calData >> 4) & 0x03;
        }
        if (accel != NULL) {
            *accel = (calData >> 2) & 0x03;
        }
        if (mag != NULL) {
            *mag = calData & 0x03;
        }
    }

    void BNO055::getVector(BNO055::vector_type_t vector_type, vector &vector) {

    }


    void BNO055::getQuaternions(vector &quaternion) {

    }

    bool BNO055::getSensorOffsets(offsets_t &offsets_type) {
        return false;
    }


    void BNO055::setSensorOffsets(const offsets_t &offsets_type) {

    }


    void BNO055::spiWriteRegister(bno055_reg_t reg, uint8_t data) {
        i2c_write_blocking(I2C_PORT, i2c_addr, (const uint8_t *) reg, length,
                           true); // true to keep master control of bus
    }

    void BNO055::spiReadRegister(bno055_reg_t reg){
        i2c_write_blocking(I2C_PORT, i2c_addr, (const uint8_t *) reg, 1, true); // true to keep master control of bus
        i2c_read_blocking(I2C_PORT, i2c_addr, data, length, false); // False - finished with bus
    }

    void BNO055::spiReadRegisters(bno055_reg_t reg, uint8_t *pData, size_t len){

    }

    void BNO055::addValidationErrors() {

    }

    void BNO055::defaultProcessRawMpu6500Data(const uint8_t (&rxBuff)[28], vector &accel, vector &gyro) {

    }


} // namespace BNO055
