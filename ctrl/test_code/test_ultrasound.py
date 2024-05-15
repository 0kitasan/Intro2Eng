#导入 GPIO库
import OPi.GPIO as GPIO
import time

#设置 GPIO 模式为 BCM
GPIO.setmode(GPIO.BOARD)

#定义 GPIO 引脚
GPIO_TRIGGER = 7
GPIO_ECHO = 12

#设置 GPIO 的工作方式 (IN / OUT)
GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
GPIO.setup(GPIO_ECHO, GPIO.IN)

def distance():
        time.sleep(0.5)
        # 发送高电平信号到 Trig 引脚
        GPIO.output(GPIO_TRIGGER, True)
        
        # 持续 10 us
        time.sleep(0.0001)
        GPIO.output(GPIO_TRIGGER, False)
        
        # start_time = time.time()
        # stop_time = time.time()
        cnt=0
        
        # 记录接收到返回超声波的时刻
        while GPIO.input(GPIO_ECHO) == 1:
                if(cnt==0):
                        start_time = time.time()
                stop_time = time.time()
                cnt+=1
                print("echo...")

        if(cnt==0):
                time_elapsed=0
        else:
                time_elapsed = stop_time - start_time
        # 声波的速度为 343m/s， 转化为 34300cm/s。
        distance = (time_elapsed * 34300) / 2
        
        return distance

if __name__ == '__main__':
        try:
                while True:
                        dist = distance()
                        print("Measured Distance = {:.2f} cm".format(dist))
                        time.sleep(1)
        
                # Reset by pressing CTRL + C
        except KeyboardInterrupt:
                print("Measurement stopped by User")
                GPIO.cleanup()
