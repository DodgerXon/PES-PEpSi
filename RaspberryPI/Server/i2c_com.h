#ifndef I2C_COM_H
#define I2C_COM_H

#include <string>

class I2C_COM {
public:
    I2C_COM();
    ~I2C_COM();
    std::string requestDataFromSlave(int address, int request);

private:
    int file;
    static constexpr const char* filename = "/dev/i2c-1";
};

#endif
