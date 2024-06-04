#ifndef DEF_MOTOR
#define DEF_MOTOR

// 定义引脚
// PWM调速（先搁置）

class Motor {
public:
  Motor(int Pin1, int Pin2);
  void run();
  void run_reverse();
  // 需要后台运行，以免阻塞线程
  void run_awhile(int duration_ms);
  void run_reverse_awhile(int duration_ms);
  void stop();

private:
  int Pin1;
  int Pin2;
  void run_awhile_thread(int duration_ms);
  void run_reverse_awhile_thread(int duration_ms);
};

#endif