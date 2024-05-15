# 进度报告 05/16 第13周

## 机械部分
* 完成了底盘和麦轮的装配
* 搜寻资料，想办法将舵机与手机支架相结合，有了初步的想法

## 控制部分

* 完成了超声波测距的代码
* 由于杜邦线不方便焊接，电机部分的控制代码尚且无法测试

<details>
  <summary>Click to view the video</summary>

  <video width="600" controls>
      <source src="https://github.com/0kitasan/demo/assets/62045828/d660f4a4-f9a2-476c-a86e-d7e5b86e4841" type="video/mp4">
  </video>

</details>

## 代码部分

先在没有摄像头的情况下，使用视频完成人脸识别代码的测试，demo视频如下：

<details>
  <summary>Click to view the video</summary>

  <video width="600" controls>
      <source src="https://github.com/0kitasan/demo/assets/62045828/1161ac87-93a4-4792-ac36-0484ebcc419e" type="video/mp4">
  </video>

  <video height="600" controls>
      <source src="https://github.com/0kitasan/demo/assets/62045828/8ce638a8-ca06-4461-af30-9338d5c1cee5" type="video/mp4">
  </video>
</details>

## 未来计划
 
* 上周采购的铜线到了，可以焊接了
<details>
  <summary>Click to view the image</summary>
  <img src="https://github.com/0kitasan/demo/assets/62045828/4abc4437-9818-4a01-b374-e7ce8504ef3f" alt="Demo Image" width="400">
</details>

* 上周采购的直流电源（可调电压）到了，焊接好后可以调试电机和电机驱动
<details>
  <summary>Click to view the image</summary>
  <img src="https://github.com/0kitasan/demo/assets/62045828/c5c39678-342f-4833-b646-81274dc1fdb6" alt="Demo Image" width="400">
  <img src="https://github.com/0kitasan/demo/assets/62045828/4abc4437-9818-4a01-b374-e7ce8504ef3f" alt="Demo Image" width="400">
</details>

* 尝试把人脸识别的代码移植到c++下，测试一下延迟
  * 如果延迟减小至一个可接受范围，则皆大欢喜
  * 如果延迟还是很大，考虑更换minipc

