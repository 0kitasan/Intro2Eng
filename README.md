# 工程学导论 项目代码

SJTU 23级《工程学导论》课程项目代码

项目名称：基于人脸识别的智能手机支架

## 开发注解

### 视觉部分

#### 环境搭建

```bash
sudo apt update
sudo apt install python3-pip
pip install opencv-python 
# 如果速度太慢的话，可以换源
pip install -i https://mirrors.aliyun.com/pypi/simple opencv-python
```

注意，py代码中的文件路径是相对于vscode的工作环境而言的，如果在最外层打开则不需要加上

`model/face_detector`是别人训练好的模型，忘记是从哪里拿过来的了...

由于原先的视频太大了（而且太长了，有1分11秒，测试的时候等的时间很长），故使用 `ffmpeg`输出二倍速版本：

```bash
ffmpeg -i input.mp4 -vf "setpts=0.5*PTS" -filter:a "atempo=2.0" output.mp4
```

通过 `pip install opencv-python`安装的opencv带有的 `ffmpeg`似乎是不带h264编码的，我在demo中只能使用mp4v；并且，opencv生成的mp4文件似乎有点问题：
尽管我压缩了分辨率，但是文件还是非常的大，因此，使用 `ffmpeg`又压缩了一遍，指令如下：

```bash
ffmpeg -i input.mp4 -c:v libx264 -crf 23 -c:a aac -strict -2 output.mp4
```

这样文件大小不仅减小了，视频也能兼容所有多媒体播放器了（本来只有比较强的可以打开）。并且，经过测试，压缩2被分辨率对于模型的识别结果无显著影响。

为了方便调试和部署，尝试把原先的代码函数化，构建为module，从而将项目模块化。

### 通信/网页调试部分

5/14：flask不知道出了什么毛病，只能显示static里的图像

经同学提醒：需要将文件映射到http上才能在网页端访问，html被映射了，但是它引用的文件没有被映射。static文件夹是flask事先定义好的，因此放在其中的文件能直接被映射。

经过测试，在 `orangepi zero2`上，网页端输出的视频大概有4s的延迟；在 `orangepi 3b`上，则是大概2s的延迟，速度都非常感人，目前在考虑把识别相关的代码移植到c++中。

### 控制部分

在orangepi上，可以用 `gpio readall`命令查看板子的引脚定义，可以加上 `watch -n 0.1 gpio readall`来实时监测引脚输出变化

关于如何控制香橙派/树莓派上的GPIO引脚，有Python和C/C++两种编程方式。

**注意：Python的引脚编号是物理引脚；C/C++的引脚定义是wPi的编号**

#### Python

直接 `sudo python3 test.py`即可运行

#### C/C++

基础编译指令：`gcc -o <output name> <src file> -l wiringPi`

如果采取面向对象的方式编程，自定义的库要写在前面：

`g++ libSonarSample.cpp libSonar.cpp -o test -l wiringPi`

像这样写是不对的：

`g++ libSonarSample.cpp -o test -l wiringPi libSonar.cpp`

这会导致在 `libSonar.cpp`中，找不到 `wiringPi`中的函数的定义。

#### 分模块控制/控制逻辑

由于控制模块全部转为c++（超声波必须c++，不然会出问题）

注意，pwm控制需要改一下引脚设置，具体见源码，这里后面再具体补

下面是最后的main函数设想：

```c++
Sonar sonar(sonar_pin);
Motor motor(motor_pin);
Servo servo(servo_pin);
FaceDetector fd(cam_index);

int main(){
    while(1){
        fd.cap_frame();
        fd.process_frame();
        switch (fd.result()){
            case RIGHT:
                motor.turn_left();
                break;
            case LEFT:
                motor.turn_right();
                break
            case UP:
                servo.down();
                break;
            case DOWN:
                servo.up();
                break;
            case MIDDLE:
                break;
            default:
                break;
        }
        if(sonar.distance()>max_threshold){
            motor.forward();
        }else if(sonar.distance()<min_threshold){
            motor.backward();
        }
    }
}
```

#### 参考

超声波测距代码直接参考以下git仓库，虽然库本身也比较简单，还是感谢作者帮我节省了时间：
https://github.com/omaraflak/HC-SR04-Raspberry-Pi-C-

## 开发日志

| 日期 | 开发进度                                                                                                                                                                                                                          |
| ---- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 4/12 | 完成人脸识别py代码的demo                                                                                                                                                                                                          |
| 4/28 | 新增cam版本以及控制代码demo                                                                                                                                                                                                       |
| 5/10 | 超声波测距代码：arduino的可以用，<br />但是发现香橙派上的用py写的死活不对                                                                                                                                                         |
| 5/13 | debug并完成了超声波测距相关代码，结果比arduino上的更准确；<br />也许以后控制代码需要全部转为c++了                                                                                                                                 |
| 5/14 | 调整了demo视频的分辨率，否则项目仓库过大；<br />由于.git占了近300MB，于是新开了一个仓库；<br />web_debugger初步构建完成                                                                                                           |
| 5/15 | 使用ffmpeg修正了demo视频无法播放和文件过大的问题；<br />经测试，因在小电脑上延迟过大，可能要将人脸识别模块改写为c++                                                                                                               |
| 5/22 | 优化视觉部分的架构，从config.py变为config.yaml；<br />进一步测试延迟，发现主要来自网页端，而非人脸识别程序；<br />还需单独测试motor和servo模块(c++)；<br />又因人脸识别本来也写了c++的版本，<br />目前在考虑要不要全部都换成c++。 |
| 6/3  | 测试并完善了motor与servo的代码；<br />尝试将库都放在一个文件中方便香橙派获取及简化编译指令                                                                                                                                        |
