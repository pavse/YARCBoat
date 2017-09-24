#define INACTIVE_PWM 8 // Level when motor does not rotate, value in range 0..127

class Motor {
  private:
    int8_t Speed = 0; // -127..+127
    byte pinPlus;
    byte pinMinus;
    byte pinPWM;

  public:
    void setPinPlus(byte boardPin) {
      pinMode(boardPin, OUTPUT);
      pinPlus = boardPin;
    }

    void setPinMinus(byte boardPin) {
      pinMode(boardPin, OUTPUT);
      pinMinus = boardPin;
    }

    void setPinPWM(byte boardPin) {
      pinMode(boardPin, OUTPUT);
      pinPWM = boardPin;
    }

    void setSpeed(int8_t newSpeed) {
      if ( newSpeed == Speed ) return;
      if ( abs(newSpeed) <= INACTIVE_PWM ) {
        Speed = 0;
      } else {
        if (Speed == 0) {
          Speed = 127;      // Speed was zero, kick the motor
        } else {
          Speed = newSpeed;
        };
      };
      int16_t pwm = abs(Speed) << 3;
      if ( Speed >= 0 ) {
        digitalWrite(pinMinus, 0);
        digitalWrite(pinPlus,  1);
      } else {
        digitalWrite(pinMinus, 1);
        digitalWrite(pinPlus,  0);
      };
        analogWrite(pinPWM, pwm);
    };

    int8_t getSpeed() {
        return Speed;
    };
};

