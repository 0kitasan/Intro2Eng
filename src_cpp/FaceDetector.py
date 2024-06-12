import cv2
import time


class FaceDetector:
    def __init__(self, model_bin, config_text, cam_index=0):
        self.net = cv2.dnn.readNetFromTensorflow(model_bin, config_text)
        self.cap = cv2.VideoCapture(cam_index)
        self.frame = None
        self.left = 0
        self.top = 0
        self.right = 0
        self.bottom = 0
        self.frame_height = 0
        self.frame_width = 0
        self.found = False
        if not self.cap.isOpened():
            raise RuntimeError("Error: Unable to open camera.")

        self.cap_frame()

    def cap_frame(self):
        start = time.time()
        success, self.frame = self.cap.read()
        if not success:
            raise RuntimeError("Error: Unable to capture frame.")
        if self.frame is not None:
            self.frame_height, self.frame_width = self.frame.shape[:2]
        else:
            raise RuntimeError("Error: No frame captured to get size.")
        end = time.time()
        print("capture time=" + str(end - start))

    def resize_frame(self):
        self.frame_height = int(self.frame_height / 2)
        self.frame_width = int(self.frame_width / 2)
        self.frame = cv2.resize(self.frame, (self.frame_width, self.frame_height))

    def process_frame(self, draw):
        if self.frame is None:
            raise RuntimeError("Error: No frame captured to process.")

        start = time.time()
        h, w, _ = self.frame.shape
        blobImage = cv2.dnn.blobFromImage(
            self.frame, 1.0, (300, 300), (104.0, 117.0, 123.0), False, False
        )
        self.net.setInput(blobImage)
        Out = self.net.forward()

        self.found = False
        for detection in Out[0, 0, :, :]:
            score = float(detection[2])
            if score > 0.7:
                self.found = True
                self.left = int(detection[3] * w)
                self.top = int(detection[4] * h)
                self.right = int(detection[5] * w)
                self.bottom = int(detection[6] * h)
                if draw == True:
                    cv2.rectangle(
                        self.frame,
                        (self.left, self.top),
                        (self.right, self.bottom),
                        (255, 0, 0),
                        2,
                    )
                    cv2.putText(
                        self.frame,
                        "score:%.2f" % score,
                        (self.left, self.top - 10),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.5,
                        (0, 0, 255),
                        1,
                    )
        end = time.time()
        print("inference latency=" + str(end - start))

    def horizontal_pos(self):
        print("Horizontal=", end="")
        if self.found:
            if self.right < self.frame_width / 2:
                print("left")
                return 1
            elif self.left > self.frame_width / 2:
                print("right")
                return 2
            else:
                print("no left or right")
                return 0
        else:
            print("Not Found!")
            return -1

    def vertical_pos(self):
        print("Vertical=", end="")
        if self.found:
            if self.top > self.frame_height / 2:
                print("down")
                return 1
            elif self.bottom < self.frame_height / 2:
                print("up")
                return 2
            else:
                print("no up or down")
                return 0
        else:
            print("Not Found!")
            return -1

    def show(self):
        if self.frame is not None:
            cv2.imshow("Face Detector", self.frame)
            key = cv2.waitKey(1)
            if key == ord("q"):
                return False
        return True

    def release(self):
        self.cap.release()
        cv2.destroyAllWindows()
