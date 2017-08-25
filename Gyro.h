#include "MPU6050.h"

#define SDA  2
#define SCL  4

class Gyro {
  private:
    MPU6050 mpu;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

  public:
    Gyro() {
      // https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/using-the-arduino-addon
      Wire.begin(SDA, SCL);

      Serial.println("MPU initialization...");
      mpu.initialize();
      Serial.println(mpu.testConnection() ? "MPU connected" : "MPU connection failed");
    };

    int8_t getRotation() {
      mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      return map(ax, -17000, 17000, -127, 127);
    };
};
