#include "wiringPi.h"
#include <stdio.h>
#define PWM_pin 21
// zero的PWM与其他引脚复用，需要在/boot/orangepiEnv.txt中修改
int main() {
  int div = 8;     // 分频因子（Divisor）
  int arr = 60000; // 计数范围（Range）
  int ccr = 3000;  // 占空比计数值
  // 频率= 24000000 / (60000 * 8) = 50Hz   sg90舵机要50Hz才能正常驱动
  if (wiringPiSetup() == -1) {
    printf("初始化失败惹＞︿＜");
  }
  pinMode(PWM_pin, PWM_OUTPUT);
  while (1) {
    pwmSetClock(PWM_pin, div);
    pwmSetRange(PWM_pin, arr);
    pwmWrite(PWM_pin, ccr);
    // 占空比duty = ccr / arr = 5.0% 对应45度位置
  }
}