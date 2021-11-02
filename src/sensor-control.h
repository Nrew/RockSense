// Libraries
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define START_CONVERSION 0x12

/**
 * @brief Commands to correspond to the addresses 
 * 
 */
typedef enum {
    CMD_READ_PRESSURE_HIGH = 0,
    CMD_READ_PRESSURE_LOW,
    CMD_READ_TEMP_HIGH, 
    CMD_READ_TEMP_LOW,
    CMD_READ_COEFFICIENTS
} commands;

/**
 * @brief A structure to represent a memory map for the MPL115A2 part.
 * 
 */
typedef struct {
    uint8_t Padc_MSB;
    uint8_t Padc_LSB;
    uint8_t Tadc_MSB;
    uint8_t Tadc_LSB;
    uint8_t a0_MSB;
    uint8_t a0_LSB;
    uint8_t b1_MSB;
    uint8_t b1_LSB;
    uint8_t b2_MSB;
    uint8_t b2_LSB;
    uint8_t c12_MSB;
    uint8_t c12_LSB;
} MPL115A2;


int file;
char *filename = "/dev/i2c-1";
uint8_t addr = 0x60; // The I2C address of the sensor.

/**
 * Attempt to connect to the i2c bus.
 * 
 * @throw EXIT_FAILURE If the bus could not be opened.
 **/
int connectI2CBus(void);

/**
 * Initalize to the sensor, with the nessasary attributes.
 **/
int initSensor(void);

/**
 * @brief 
 * 
 * @return int 
 */
int startConversion(void);

/**
 * Register the coefficents values and map them to @link{MPL115A2} struct.
 * 
 * @param dev Pointer to a structure MPL115A2 to represent the memory map.
 * @return int
 **/
int registerCoefficients(MPL115A2* dev);

/**
 * @brief 
 * 
 * @param dev 
 * @return int 
 */
int regTempAndPressure( MPL115A2* dev);

/**
 * @brief 
 * 
 * @param LSB 
 * @param MSB 
 * @return float 
 */
float toFloatPnt(uint8_t LSB, uint8_t MSB);

/**
 * @brief Calculate the pressure from the stored memory map.
 * 
 * @param dev Memory Structure to map the MSB and LSB from.
 * @return float The claculated pressure.
 */
float calculatePressure(MPL115A2* dev);

/**
 * @brief Perform the calculation of the temprature. 
 * 
 * @param dev Memory Structure to map the MSB and LSB from.
 * @return flaot The temprature calcuated.
 */
float calcTemp(MPL115A2* dev);