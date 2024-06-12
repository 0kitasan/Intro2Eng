#include "libControl.hpp"
#include <cassert>
#include <iostream>
#include <pybind11/embed.h> // 包含 pybind11 的头文件
#include <string>
#include <thread>
namespace py = pybind11;

#define MOTOR_PIN1 2
#define MOTOR_PIN2 5
#define MOTOR_PIN3 7
#define MOTOR_PIN4 8
#define SERVO_PIN 6
#define SONAR_TRIGGER 10
#define SONAR_ECHO 11
#define MODEL_PATH "assets/model/face_detector/opencv_face_detector_uint8.pb"
#define CONFIG_PATH "assets/model/face_detector/opencv_face_detector.pbtxt"

// ms
#define DURATION 100
#define DELAY 50

int main(int argc, char *argv[]) {
  // 使用 assert 确保至少有两个参数传递给程序
  assert(argc > 2 && "At least 2 arguments are required");

  // 初始化布尔变量
  bool should_show = false;
  bool should_draw = false;

  // 将命令行参数转换为整数并设置布尔变量
  int arg1 = std::stoi(argv[1]);
  int arg2 = std::stoi(argv[2]);

  should_show = arg1;
  should_draw = arg2;

  // 初始化 Python 解释器
  py::scoped_interpreter guard{};
  // 在RedmiBook上，给构造函数传入string类型的0会有问题的
  // 要测试就直接在构造函数里面写0,要么不写，就默认为0
  std::string cam_index = "/dev/video1";
  int frame_num = 0;
  int horizontal_pos, vertical_pos;

  try {

    // 导入 Python 模块 FaceDetector
    py::module example = py::module::import("FaceDetector");
    // 初始化 FaceDetector 类
    py::object FaceDetector = example.attr("FaceDetector");
    auto fd = FaceDetector(MODEL_PATH, CONFIG_PATH, cam_index);

    // 各个部件的初始化与实例化
    if (wiringPiSetup() == -1) {
      std::cout << "wiringPiSetup error" << std::endl;
      return -1;
    }

    Car car(MOTOR_PIN1, MOTOR_PIN2, MOTOR_PIN3, MOTOR_PIN4);
    car.set_default_dir(1, 0);
    Servo servo(SERVO_PIN);
    Sonar sonar(SONAR_TRIGGER, SONAR_ECHO);
    bool found = false;

    // 主循环
    while (true) {
      frame_num++;
      std::cout << "frame num=" << frame_num << std::endl;
      // 调用 Python 类的方法
      fd.attr("cap_frame")();
      fd.attr("resize_frame")();
      fd.attr("process_frame")(should_draw);
      if (should_show) {
        fd.attr("show")();
      }
      found = fd.attr("found").cast<bool>();
      std::cout << "found=" << found << std::endl;
      // 获取结果
      horizontal_pos = fd.attr("horizontal_pos")().cast<int>();
      vertical_pos = fd.attr("vertical_pos")().cast<int>();

      // std::cout << "Distance is " << sonar.distance(30000) << " cm."
      //  << std::endl;

      std::cout << "-------------------" << std::endl;

      switch (horizontal_pos) {
      case 1: // left
        car.turn_left(DURATION);
        break;
      case 2: // right
        car.turn_right(DURATION);
        break;
      default:
        car.stop();
        break;
      }

      switch (vertical_pos) {
      case 1: // down
        servo.rotate_to_angle(150);
        break;
      case 2: // up
        servo.rotate_to_angle(90);
        break;
      default:
        servo.rotate_to_angle(120);
        break;
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    }

    fd.attr("release")();
    car.stop();
  } catch (const py::error_already_set &e) {
    std::cerr << "Python error: " << e.what() << std::endl;
  }

  return 0;
}
