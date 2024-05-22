import cv2

try:
    # 尝试相对导入，当作为模块被其他文件导入时使用
    from .detector import detector
    from .config_loader import CONFIG
except ImportError:
    # 如果相对导入失败，尝试绝对导入，适用于直接运行脚本
    from detector import detector
    from config_loader import CONFIG

video_path = CONFIG["Path"]["video"][1]
output_path = CONFIG["Path"]["output"][1]


def demo_show():
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        print("Error: Unable to open video.")
        exit()

    # 定义输出视频的文件名、帧率和编解码器
    output_file = output_path
    fourcc = cv2.VideoWriter_fourcc(*"mp4v")
    fps = cap.get(cv2.CAP_PROP_FPS)
    print("fps=" + str(fps))

    # 获取视频的帧宽度和高度
    frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    compress_rate = 2
    new_size = (int(frame_width / compress_rate), int(frame_height / compress_rate))
    # 创建视频写入对象
    out = cv2.VideoWriter(output_file, fourcc, fps, new_size)
    while True:
        # Read frame from the capture
        success, img = cap.read()
        if success:
            img = cv2.resize(img, new_size)
            img = detector(img)

            cv2.imshow("result", img)
            out.write(img)

            if cv2.waitKey(30) & 0xFF == ord("q"):
                break
        else:
            # 视频已结束，退出循环
            break

    cap.release()
    out.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    demo_show()
