#include "i2c_com.h"
#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <cstdio>

I2C_COM::I2C_COM() {
    file = open(filename, O_RDWR);
    if (file < 0) {
        perror("Failed to open the i2c bus");
    }
}

I2C_COM::~I2C_COM() {
    close(file);
}

std::string I2C_COM::requestDataFromSlave(int address, int request) {
    unsigned char buf[4];
    buf[0] = request;
    
    if (ioctl(file, I2C_SLAVE, address) < 0) {
        perror("Failed to set slave address");
        return ""; // Return an empty string to indicate failure
    }
    
    if (write(file, buf, 1) != 1) {
        perror("Failed to write data to slave");
    }
    if (read(file, buf, 2) != 2) {
        perror("Failed to read data from slave");
    }
    float value = (buf[0] >> 8) | buf[0];

    char str_value[10];
    snprintf(str_value, sizeof(str_value), "%.1f", value);

    std::cout << "Received value from slave " << std::hex << address << ": " << value << std::endl;

    return std::string(str_value);
}
