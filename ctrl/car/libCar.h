#ifndef DEF_CAR
#define DEF_CAR

// 定义引脚
// PWM调速（先搁置）

class Car {
public:
  Car(int Motor1Pin1_, int Motor1Pin2_, int Motor2Pin1_, int Motor2Pin2_);
  ~Car();
  void test_motor1_dir();
  void test_motor2_dir();
  void set_default_dir(bool motor1_dir_, bool motor2_dir_);
  void run(bool isForward, int duration);
  void stop();
  void turn_left(int duration);
  void turn_right(int duration);

private:
  int Motor1Pin1, Motor1Pin2, Motor2Pin1, Motor2Pin2;
  bool motor1_dir = true;
  bool motor2_dir = true;
  void motor1_run(bool isForward);
  void motor2_run(bool isForward);
};

#endif