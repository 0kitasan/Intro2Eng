import cv2

try:
    # 尝试相对导入，当作为模块被其他文件导入时使用
    from .config_loader import CONFIG
except ImportError:
    # 如果相对导入失败，尝试绝对导入，适用于直接运行脚本
    from config_loader import CONFIG

model_bin = CONFIG["Path"]["model"]["bin"]
config_text = CONFIG["Path"]["model"]["text"]
net = cv2.dnn.readNetFromTensorflow(model_bin, config=config_text)


def detector(img):
    h, w, c = img.shape
    blobImage = cv2.dnn.blobFromImage(
        img, 1.0, (300, 300), (104.0, 117.0, 123.0), False, False
    )
    net.setInput(blobImage)
    Out = net.forward()

    for detection in Out[0, 0, :, :]:
        score = float(detection[2])
        if score > 0.7:
            left = detection[3] * w
            top = detection[4] * h
            right = detection[5] * w
            bottom = detection[6] * h
            cv2.rectangle(
                img, (int(left), int(top)), (int(right), int(bottom)), (255, 0, 0), 2
            )
            cv2.putText(
                img,
                "score:%.2f" % score,
                (int(left), int(top) - 10),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.5,
                (0, 0, 255),
                1,
            )
    return img
