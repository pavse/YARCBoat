#define INACTIVE_PWM 8 // Level when motor does not rotate, value in range 0..127

class Motor {
    int8_t Speed = 0; // -127..+127
    byte pinPlus;
    byte pinMinus;

  public: void setPinPlus(byte boardPin) {
      pinMode(boardPin, OUTPUT);
      pinPlus = boardPin;
    }

  public: void setPinMinus(byte boardPin) {
      pinMode(boardPin, OUTPUT);
      pinMinus = boardPin;
    }

  public: void setSpeed(int8_t newSpeed) {
      if ( abs(newSpeed) <= INACTIVE_PWM ) {
        Speed = 0;
      } else {
        Speed = newSpeed;
      };
      int16_t pwm = abs(newSpeed) << 3;
      if ( Speed >= 0 ) {
        analogWrite(pinMinus, 0);
        analogWrite(pinPlus,  pwm);
      } else {
        analogWrite(pinPlus,  0);
        analogWrite(pinMinus, pwm);
      };
    };
};

