// https://github.com/jrowberg/i2cdevlib/tree/master/Arduino
// put MPU6050/ and I2Cdev/ into the {ArduinoIDEhome}/libraries/
#include "MPU6050.h"

#define SDA  2
#define SCL  4

class Gyro {
  private:
    MPU6050 mpu;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    byte    shift;
    String  status;

  public:
    Gyro() {
      /* https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/using-the-arduino-addon
         A lot of the core Arduino libraries have been re-written to work for the ESP8266:
         Wire – The ESP8266 should work with any I2C sensor you can throw at it –
         just use the same Wire API calls you’re used to. There are a few differences:
         Pin definition: The ESP2866 doesn’t actually have any hardware I2C pins –
         those labeled on the Thing are the default, but you can actually use any two pins
         as SDA and SCL. Calling Wire.begin() will assume pins 2 and 14 are SDA and SCL,
         but you can manually set them to any other pin by calling Wire.begin([SDA], [SCL]). */
      Wire.begin(SDA, SCL);

      status = "MPU initialization...";
      mpu.initialize();
      status = mpu.testConnection() ? "MPU connected" : "MPU connection failed";
    };

    int8_t getRotation() {
      mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      int result = ax >> shift;
      if (result >  127) result =  127;
      if (result < -127) result = -127;
      return (int8_t)result;
      //return map(ax, -17000, 17000, -127, 127);
    };

    void setShift(byte value){
        if (0 <= value && value <=10) {
            shift = value;
        };
    };

    String getStatus(){
        return status;
    };
};
