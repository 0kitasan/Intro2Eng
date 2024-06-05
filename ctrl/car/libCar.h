#ifndef DEF_CAR
#define DEF_CAR

// 定义引脚
// PWM调速（先搁置）

class Car {
public:
  Car(int Motor1Pin1_, int Motor1Pin2_, int Motor2Pin1_, int Motor2Pin2_);
  ~Car();
  void run(bool direction, int duration);
  void stop();
  void turn_left(int duration);
  void turn_right(int duration);

private:
  int Motor1Pin1, Motor1Pin2, Motor2Pin1, Motor2Pin2;
};

#endif