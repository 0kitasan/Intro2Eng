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
# 不加这一串东西，程序在当前目录是跑不了了，但是在外面的main是跑得了的，大概是因为文件结构的关系

def demo_show():
    cap = cv2.VideoCapture(config.VIDEO_PATHS[1])
    if not cap.isOpened():
        print("Error: Unable to open video.")
        exit()

    model_bin = config.MODEL_PATHS[0]
    config_text = config.MODEL_PATHS[1]
    net = cv2.dnn.readNetFromTensorflow(model_bin, config=config_text)

    # 定义输出视频的文件名、帧率和编解码器
    output_file = config.OUTPUT_PATHS[1]
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    fps = cap.get(cv2.CAP_PROP_FPS)
    print("fps="+str(fps))

    # 获取视频的帧宽度和高度
    frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    compress_rate=2
    new_size=(int(frame_width/compress_rate),int(frame_height/compress_rate))
    # 创建视频写入对象
    out = cv2.VideoWriter(output_file, fourcc, fps, new_size)
    while True:
        # Read frame from the capture
        success, img = cap.read()
        if success:
            img=cv2.resize(img,new_size)
            h, w, c = img.shape
            blobImage = cv2.dnn.blobFromImage(img, 1.0, (300, 300), (104.0, 117.0, 123.0), False, False)
            net.setInput(blobImage)
            Out = net.forward()
            t, _ = net.getPerfProfile()
            label = 'Inference time: %.2f ms' % (t * 1000.0 / cv2.getTickFrequency())
            cv2.putText(img, label, (0, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)

            for detection in Out[0,0,:,:]:
                score = float(detection[2])
                objIndex = int(detection[1])
                if score > 0.7:
                    # print("face detected.")
                    left = detection[3]*w
                    top = detection[4]*h
                    right = detection[5]*w
                    bottom = detection[6]*h
                    # 绘制
                    cv2.rectangle(img, (int(left), int(top)), (int(right), int(bottom)), (255, 0, 0), thickness=2)
                    cv2.putText(img, "score:%.2f"%score, (int(left), int(top)-1), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 1)
            
            cv2.imshow("result", img)
            out.write(img)

            if cv2.waitKey(30) & 0xff == ord('q'):
                break
        else:
            # 视频已结束，退出循环
            break

    cap.release()
    out.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    demo_show()
