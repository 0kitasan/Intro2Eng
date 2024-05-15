# 进度报告 05/16 第13周

## 机械部分
* 完成了底盘和麦轮的装配
* 搜寻资料，想办法将舵机与手机支架相结合，有了初步的想法

## 控制部分

* 完成了超声波测距的代码
* 由于杜邦线不方便焊接，电机部分的控制代码尚且无法测试

## 代码部分

先在没有摄像头的情况下，使用视频完成人脸识别代码的测试，demo视频如下：

<details>
  <summary>Click to view the video</summary>

<video width="600" controls>
    <source src="https://github.com/0kitasan/demo/assets/62045828/27193b74-11e5-4481-9857-5b2d88785f9f" type="video/mp4">
    Your browser does not support the video tag.
  </video>

  [Download the video](https://github.com/0kitasan/demo/assets/62045828/27193b74-11e5-4481-9857-5b2d88785f9f)

</details>


## 未来计划

* 上周采购的铜线到了，可以焊接了
* 上周采购的直流电源（可调电压）到了，焊接好后可以调试电机和电机驱动
* 尝试把人脸识别的代码移植到c++下，测试一下延迟
  * 如果延迟减小至一个可接受范围，则皆大欢喜
  * 如果延迟还是很大，考虑更换minipc

