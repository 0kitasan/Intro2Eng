#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
/*
运行：sudo ./wiring_c_io_set [引脚 值]
编译：gcc wiring_c_io_set.c -o wiring_c_io_set -L lib -l wiringPi -l pthread (需已安装wiringPi)
*/

#define Set_io_pin 2					//定义需要控制哪个引脚（wPi）

int pin,value,count=5;

int main(int args, char *argv[])
{
	if((argv[1])&&(argv[2])){
		wiringPiSetup();
		pin=atoi(argv[1]);
		value=atoi(argv[2]);
		pinMode(pin,OUTPUT);
		digitalWrite(pin,value);
	}
	else{
		int i=0;
		wiringPiSetup();					//选择WPI编码方式
		pinMode(Set_io_pin, OUTPUT);    	//设置为输出模式
		for (i=0;i<count;i++){
			digitalWrite(Set_io_pin,1);    		//控制引脚高电平
			delay(500);
			digitalWrite(Set_io_pin,0);    		//控制引脚低电平
			delay(500);
		}
	}
}
