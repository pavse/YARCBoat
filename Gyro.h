#include "Wire.h"
#include "MPU6050.h"

class Gyro {
  private:
    MPU6050 mpu;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

  public:
    Gyro() {
      Wire.begin();
      Serial.println("Initialize MPU");
      mpu.initialize();
      Serial.println(mpu.testConnection() ? "MPU connected" : "MPU connection failed");
    };

    int8_t getRotation() {
      mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      return map(ax, -17000, 17000, -127, 127);
    };
};
