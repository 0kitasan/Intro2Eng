import cv2

try:
    # 尝试相对导入，当作为模块被其他文件导入时使用
    from .config_loader import CONFIG
except ImportError:
    # 如果相对导入失败，尝试绝对导入，适用于直接运行脚本
    from config_loader import CONFIG

video_path = CONFIG["Path"]["video"][1]


def video_show():
    # 打开视频文件
    cap = cv2.VideoCapture(video_path)

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
        cv2.imshow("Frame", frame)

        # 检查是否按下 'q' 键，如果按下则退出循环
        if cv2.waitKey(25) & 0xFF == ord("q"):
            break

    # 释放资源并关闭窗口
    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    video_show()
