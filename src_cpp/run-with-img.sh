#!/bin/bash

# 定义密码变量
PASSWORD="orangepi"

# 使用 sudo -S 并传递密码
# sudo -E 保证 python 在普通而非 sudo 环境下运行
echo $PASSWORD | sudo -S -E ./build/main 1 1
