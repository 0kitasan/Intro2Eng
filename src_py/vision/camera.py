import cv2
import time

try:
    # 尝试相对导入，当作为模块被其他文件导入时使用
    from .detector import detector
    from .config_loader import CONFIG
except ImportError:
    # 如果相对导入失败，尝试绝对导入，适用于直接运行脚本
    from detector import detector
    from config_loader import CONFIG


def cam_show(cam_index=0):
    cap = cv2.VideoCapture(cam_index)
    if not cap.isOpened():
        print("Error: Unable to open camera.")
        exit()
    quit = False
    while True and not quit:
        start_time = time.time()
        # Read frame from the capture
        success, img = cap.read()
        if success:
            img = detector(img)
            end_time = time.time()
            # label = "Inference time: %.2f ms" % (t * 1000.0 / cv2.getTickFrequency())
            latency = end_time - start_time
            label = "Read and Inference time: %.2f ms" % (latency * 1000)
            cv2.putText(
                img, label, (0, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2
            )
            cv2.imshow("result", img)
            if cv2.waitKey(30) & 0xFF == ord("q"):
                quit = True
                break
        else:
            # 视频已结束，退出循环
            print("face detection end...")
            break
    cap.release()
    cv2.destroyAllWindows()


def cam_send(cam_index=0):
    # 参数为摄像头索引，通常是0，函数中默认定义为0
    # 在orangepi上，是"/dev/video1"
    cap = cv2.VideoCapture(cam_index)
    if not cap.isOpened():
        print("Error: Unable to open camera.")
        exit()
    while True:
        start_time = time.time()
        # Read frame from the capture
        success, img = cap.read()
        if success:
            img = detector(img)
            end_time = time.time()
            # label = "Inference time: %.2f ms" % (t * 1000.0 / cv2.getTickFrequency())
            latency = end_time - start_time
            label = "Read and Inference time: %.2f ms" % (latency * 1000)
            cv2.putText(
                img, label, (0, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2
            )
            ret, buffer = cv2.imencode(".jpg", img)
            img = buffer.tobytes()
            # 一旦加上了yield，该函数就会被视为生成器函数，因此只能写成两个函数
            yield (b"--frame\r\n" b"Content-Type: image/jpeg\r\n\r\n" + img + b"\r\n")
        else:
            # 视频已结束，退出循环
            break
    cap.release()
    cv2.destroyAllWindows()


video_path_4test = CONFIG["Path"]["video"][1]

if __name__ == "__main__":
    # cam_show()
    cam_show(video_path_4test)
