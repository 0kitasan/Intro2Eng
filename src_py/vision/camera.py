import cv2

import sys
import os

# 获取当前文件的目录
current_dir = os.path.dirname(os.path.abspath(__file__))
# 获取项目根目录
project_root = os.path.abspath(os.path.join(current_dir, ".."))
# 将项目根目录添加到 sys.path
if project_root not in sys.path:
    sys.path.append(project_root)
# 现在可以导入 config 模块
import config


def cam_show(cam_index=0):
    # 参数为摄像头索引，通常是0，函数中默认定义为0
    # 在orangepi上，是"/dev/video1"
    cap = cv2.VideoCapture(cam_index)
    if not cap.isOpened():
        print("Error: Unable to open camera.")
        exit()

    model_bin = config.MODEL_PATHS[0]
    config_text = config.MODEL_PATHS[1]

    net = cv2.dnn.readNetFromTensorflow(model_bin, config=config_text)

    while True:
        # Read frame from the capture
        success, img = cap.read()
        if success:
            h, w, c = img.shape

            blobImage = cv2.dnn.blobFromImage(
                img, 1.0, (300, 300), (104.0, 117.0, 123.0), False, False
            )
            net.setInput(blobImage)
            Out = net.forward()
            t, _ = net.getPerfProfile()
            label = "Inference time: %.2f ms" % (t * 1000.0 / cv2.getTickFrequency())
            cv2.putText(
                img, label, (0, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2
            )

            for detection in Out[0, 0, :, :]:
                score = float(detection[2])
                objIndex = int(detection[1])
                if score > 0.7:
                    # print("face detected.")
                    left = detection[3] * w
                    top = detection[4] * h
                    right = detection[5] * w
                    bottom = detection[6] * h
                    # 绘制
                    cv2.rectangle(
                        img,
                        (int(left), int(top)),
                        (int(right), int(bottom)),
                        (255, 0, 0),
                        thickness=2,
                    )
                    cv2.putText(
                        img,
                        "score:%.2f" % score,
                        (int(left), int(top) - 1),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.5,
                        (0, 0, 255),
                        1,
                    )

            cv2.imshow("result", img)

            if cv2.waitKey(30) & 0xFF == ord("q"):
                break
        else:
            # 视频已结束，退出循环
            break
    cap.release()
    cv2.destroyAllWindows()


def cam_send(cam_index=0):
    cap = cv2.VideoCapture(cam_index)
    if not cap.isOpened():
        print("Error: Unable to open camera.")
        exit()

    model_bin = config.MODEL_PATHS[0]
    config_text = config.MODEL_PATHS[1]

    net = cv2.dnn.readNetFromTensorflow(model_bin, config=config_text)

    while True:
        # Read frame from the capture
        success, img = cap.read()
        if success:
            h, w, c = img.shape

            blobImage = cv2.dnn.blobFromImage(
                img, 1.0, (300, 300), (104.0, 117.0, 123.0), False, False
            )
            net.setInput(blobImage)
            Out = net.forward()
            t, _ = net.getPerfProfile()
            label = "Inference time: %.2f ms" % (t * 1000.0 / cv2.getTickFrequency())
            cv2.putText(
                img, label, (0, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2
            )

            for detection in Out[0, 0, :, :]:
                score = float(detection[2])
                objIndex = int(detection[1])
                if score > 0.7:
                    # print("face detected.")
                    left = detection[3] * w
                    top = detection[4] * h
                    right = detection[5] * w
                    bottom = detection[6] * h
                    # 绘制
                    cv2.rectangle(
                        img,
                        (int(left), int(top)),
                        (int(right), int(bottom)),
                        (255, 0, 0),
                        thickness=2,
                    )
                    cv2.putText(
                        img,
                        "score:%.2f" % score,
                        (int(left), int(top) - 1),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.5,
                        (0, 0, 255),
                        1,
                    )

            ret, buffer = cv2.imencode(".jpg", img)
            img = buffer.tobytes()
            yield (b"--frame\r\n" b"Content-Type: image/jpeg\r\n\r\n" + img + b"\r\n")

            if cv2.waitKey(30) & 0xFF == ord("q"):
                break
        else:
            # 视频已结束，退出循环
            break
    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    cam_show()
