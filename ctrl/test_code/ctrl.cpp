#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define PWM_PIN      2          //设置输出 PWM 引脚为 wiP 2
#define PWM_CYCLE    200        //设置 PMW 的周期为 20ms
#define PWM_DUTY_MAX 25         //设置最大脉宽为 2.5ms，即占空比为 12.5%
#define PWM_DUTY_MIN 5          //设置最大脉宽为 0.5ms，即占空比为 2.5%

int main(void)
{
        if (wiringPiSetup() == -1)
        	exit(1);

        softPwmCreate(PWM_PIN, PWM_DUTY_MAX, PWM_CYCLE);        //初始化 PWM 输出引脚

        int val = PWM_DUTY_MAX;        //脉冲宽度变化量
        int mark = 0;                  //转向标志

        while (1) {
			if (mark == 0)
				val--;
            else
				val++;

            if (val <= PWM_DUTY_MIN)
                    mark = 1;
            if (val >= PWM_DUTY_MAX)
                    mark = 0;

            softPwmWrite(PWM_PIN, val);
            delay(100);
        }

    return 0;
}

