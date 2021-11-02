/**
 * @date Sept 28, 2021
 * @author Andrew Sayegh
 * @version 1.0v
 * @brief Object class to handle the functionality of the controling the sensor
 */

#include "sensor-control.h"

float pressure ;
float temp;

int connectI2CBus(void) {
    if ((file = open(filename, O_RDWR)) < 0 ) {
        perror("Failed to open bus.");
        return EXIT_FAILURE;
    }

    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        perror("Failed to aquire bus access.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Initalize the sensor.
 * 
 * @return int 
 */
int initSensor(void) { 

    if (connectI2CBus() != EXIT_SUCCESS) {
        exit(1);
    }

    MPL115A2 dev;

    if (registerCoefficients(&dev) != EXIT_SUCCESS) {

    }
    if (regTempAndPressure(&dev) != EXIT_SUCCESS) {

    }

    pressure = calculatePressure(&dev);
    temp = calcTemp(&dev);

    printf("Pressure: %.2f kPa, Temp: %.2f \n", pressure, temp );

    return EXIT_SUCCESS;}


int startConversion(void) {
    // Set the buffer to the write coeffients 
    uint8_t convbuff = {START_CONVERSION};

    if (write(file, &convbuff, 1) != 1) {
        perror("Failed to write to the i2c bus.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int registerCoefficients(MPL115A2* dev){

    // Set the buffer to the read coeffients 
    uint8_t buffer = {CMD_READ_COEFFICIENTS};
    if (write(file, &buffer, 1) != 1) {
        perror("Failed to write to the i2c bus.");
        return EXIT_FAILURE;
    }

    uint8_t rxbuff[8] = {0x00};
    if (read(file, &rxbuff, 8) != 8) {
        perror("Failed to read from the i2c bus.");
        return EXIT_FAILURE;
    }

    // Capture all the coeffient data and map it to the MPL115A2 structure
    dev->a0_MSB = rxbuff[0];
    dev->a0_LSB = rxbuff[1];
    dev->b1_MSB = rxbuff[2];
    dev->b1_LSB = rxbuff[3];
    dev->b2_MSB = rxbuff[4];
    dev->b2_LSB = rxbuff[5];
    dev->c12_MSB = rxbuff[6];
    dev->c12_LSB = rxbuff[7];


    return EXIT_SUCCESS;
}

int regTempAndPressure( MPL115A2* dev) {
    startConversion();

    uint8_t wxbuff = {CMD_READ_PRESSURE_HIGH};

    if (write(file, &wxbuff, 1) != 1) {
        perror("Failed to write from the i2c bus.");
        return EXIT_FAILURE;
    }

    uint8_t rxbuff[4] = {wxbuff}; 
    
    if (read(file, &rxbuff, 4) != 4) {
        perror("Failed to read from the i2c bus.");
        return EXIT_FAILURE;
    }

    dev->Padc_MSB = rxbuff[0];
    dev->Padc_LSB = rxbuff[1];
    dev->Tadc_MSB = rxbuff[2];
    dev->Tadc_LSB = rxbuff[3];

    return EXIT_SUCCESS;
}


float toFloatPnt(uint8_t LSB, uint8_t MSB) {
    return (MSB << 8) + LSB;
}


float calculatePressure(MPL115A2* dev) {
    uint32_t pcomp = toFloatPnt(dev->a0_LSB, dev->a0_MSB) 
    + (toFloatPnt(dev->b1_LSB, dev->a0_MSB) 
    + toFloatPnt(dev->c12_LSB, dev->c12_MSB) 
    * toFloatPnt(dev->Tadc_LSB, dev->Tadc_MSB))
    * toFloatPnt(dev->Padc_LSB, dev->Padc_MSB) 
    + toFloatPnt(dev->b2_LSB, dev->b2_MSB)
    * toFloatPnt(dev->Tadc_LSB, dev->Tadc_MSB);

    return pcomp * ((115-50)/1023) + 50;
}

float calcTemp(MPL115A2* dev) {
    return toFloatPnt(dev->Tadc_LSB, dev->Tadc_MSB);
}


int main(void) {
    return initSensor();
}