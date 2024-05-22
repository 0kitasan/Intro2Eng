# 导入所需模块
from flask import Flask, render_template, Response
import cv2

from src_py.vision.camera import cam_send

from src_py.vision.config_loader import CONFIG

app = Flask(__name__)
app.cam_index_ = 0  # 摄像头索引


# 视频流处理函数
def video_stream():
    # 本地视频文件路径，注意：如果在vscode中启动，路径是相对vscode工作目录的
    video_path = CONFIG["Path"]["video"][1]
    # 打开视频文件
    cap = cv2.VideoCapture(video_path)
    while cap.isOpened():
        # 读取视频帧
        ret, frame = cap.read()
        if not ret:
            break
        # 将帧编码为 JPEG 格式
        ret, jpeg = cv2.imencode(".jpg", frame)
        # 将编码后的帧作为字节流返回给客户端
        yield (
            b"--frame\r\n"
            b"Content-Type: image/jpeg\r\n\r\n" + jpeg.tobytes() + b"\r\n"
        )
    # 关闭视频文件
    cap.release()


# 视频流路由
@app.route("/video_feed")
def video_feed():
    # 返回视频流响应
    return Response(
        video_stream(), mimetype="multipart/x-mixed-replace; boundary=frame"
    )
    # return Response(
    #     cam_send(app.cam_index_),
    #     mimetype="multipart/x-mixed-replace; boundary=frame",
    # )


# 主页路由
@app.route("/")
def index():
    # 渲染主页模板
    return render_template("index.html")


@app.route("/video")
def video():
    return render_template("video.html")


# 启动 Flask 应用
if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True, use_reloader=False)
