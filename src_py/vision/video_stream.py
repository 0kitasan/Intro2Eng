import cv2

import sys
import os
# 获取当前文件的目录
current_dir = os.path.dirname(os.path.abspath(__file__))
# 获取项目根目录
project_root = os.path.abspath(os.path.join(current_dir, '..'))
# 将项目根目录添加到 sys.path
if project_root not in sys.path:
    sys.path.append(project_root)
# 现在可以导入 config 模块
import config

def video_show():
    # 打开视频文件
    cap = cv2.VideoCapture(config.VIDEO_PATHS[0]) 

    # 检查视频是否成功打开
    if not cap.isOpened():
        print("Error: Failed to open video file.")
        exit()

    # 循环读取视频帧
    while True:
        # 读取一帧视频
        ret, frame = cap.read()

        # 检查是否成功读取视频帧
        if not ret:
            print("Error: Failed to read frame.")
            break

        # 在这里可以对每一帧进行处理，比如显示、保存等

        # 显示当前帧
        cv2.imshow('Frame', frame)

        # 检查是否按下 'q' 键，如果按下则退出循环
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break

    # 释放资源并关闭窗口
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    video_show()
