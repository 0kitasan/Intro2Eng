cmake_minimum_required(VERSION 3.12)
project(IEproject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 尝试找到 pybind11 包
find_package(pybind11 QUIET)
# 尝试找到 wiringPi 库
find_library(WIRINGPI_LIB wiringPi)
# 定义一个变量来选择路径，路径由用户确定
set(USER_NAME "orangepi")

if(pybind11_FOUND)
    message(STATUS "Found pybind11!")
else()
    message(STATUS "pybind11 not found, trying to set pybind11_DIR manually")
    set(pybind11_DIR "/home/${USER_NAME}/.local/lib/python3.10/site-packages/pybind11/share/cmake/pybind11")
    find_package(pybind11 REQUIRED)
endif()

# 添加可执行文件
add_executable(main main.cpp)

# 链接 pybind11
target_link_libraries(main PRIVATE pybind11::embed ${WIRINGPI_LIB})
