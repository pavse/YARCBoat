
#include "Motor.h"
#include "Gyro.h"

class Boat {

private:
    byte   Speed = 0;       // Allowed range is 0..127
    int8_t Rotation = 0;    // counterclockwise < 0 < clockwise
  public:
    bool   Reverse = false;
    Motor  motorLeft;
    Motor  motorRight;
    Gyro   boatGyro;

    void setSpeed(int newSpeed) {
      if ( 0 <= newSpeed and newSpeed <= 127 ) {
        Speed = newSpeed;
      };
    };

    void setRotation(int newRotation) {
      if ( -50 <= newRotation and newRotation <= 50 ) {
        Rotation = newRotation;
      };
    };

    void updateMotors() {
      int motLeft;
      int motRight;
      if ( Reverse ) {
          motLeft  = -Speed - Rotation << 3;
          motRight = -Speed + Rotation << 3;
      } else {
          motLeft  =  Speed + Rotation << 3;
          motRight =  Speed - Rotation << 3;
      }

      int motMax = abs(motLeft);
      if (motMax < abs(motRight) ) {
        motMax = abs(motRight);
      };
      if (motMax > 127) {
        motLeft  = (int32_t)motLeft  * 127 / motMax;
        motRight = (int32_t)motRight * 127 / motMax;
      };
      motorLeft.setSpeed(motLeft);
      motorRight.setSpeed(motRight);
    };
};
