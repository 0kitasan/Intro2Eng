#ifndef DEF_SERVO
#define DEF_SERVO

class Servo {
public:
  Servo(int pwm_pin_);
  void rotate_to_angle(int angle);

private:
  int pwm_pin;
  int cycle = 200;   // 设置 PMW 的周期为 20ms
  int duty_max = 25; // 设置最大脉宽为 2.5ms，即占空比为 12.5%
  int duty_min = 5;  // 设置最小脉宽为 0.5ms，即占空比为 2.5%
};

#endif