#ifndef DEF_SONAR
#define DEF_SONAR

// 定义引脚
// PWM调速（先搁置）

class Motor {
public:
  Motor(int Pin1, int Pin2, bool direction);
  void run();

private:
  int Pin1;
  int Pin2;
  // 表示正转或反转，由于连线可能连反
  bool direction = 1;
};

#endif
