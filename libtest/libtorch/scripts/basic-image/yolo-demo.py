
import onnxruntime as rt
import numpy as np
import cv2
import  matplotlib.pyplot as plt
from ultralytics import YOLO
import click
import os
from utils import nice_colors


def draw(img, xscale, yscale, results):
  for result in results:
    label2name = result.names
    for box in result.boxes:
      pos = box.xyxy.cpu().numpy().squeeze().astype(np.int16).tolist()
      score = box.conf.cpu().item()
      label = int(box.cls.cpu().item())
      name = label2name[label]
      # print(f"{name}: {score}, {pos}, {pos2}, {label}")
      text = f"{name}: {score:.2f}"
      # draw rectrange and label with cv2
      font_size = 0.7
      lefttop = (int(pos[0]*xscale), int(pos[1]*yscale))
      rightbottom = (int(pos[2]*xscale), int(pos[3]*yscale))
      cv2.rectangle(img, lefttop, rightbottom, (0, 255, 0), 2)
      cv2.rectangle(img, lefttop, (lefttop[0]+len(text)*12, lefttop[1]- 14), nice_colors[len(nice_colors)-label-1], -1)
      cv2.putText(img, text, lefttop, cv2.FONT_HERSHEY_SIMPLEX, font_size, (255,255,255), 2)
      # draw rectrange and label with plt


@click.command()
@click.argument('model_path', default='model/yolov8n.pt')
@click.argument('img_path', default='data/crowd.jpeg')
def run(model_path, img_path):
    height, width = 640, 640
    img0 = cv2.imread(img_path)
    x_scale = img0.shape[1] / width
    y_scale = img0.shape[0] / height
    img = cv2.resize(img0, (width, height))
    img = img / 255. # normalize to [0, 1]
    img = np.transpose(img, (2, 0, 1)) # convert origin format HWC to CHW
    img = np.expand_dims(img, axis=0)

    model = YOLO(model_path)
    results = model.predict(source=img, project="detect", name="crowd")

    # dump detections to json file
    # targets = [json.loads(p.tojson()) for p in results]
    # with open('results.json', 'w') as f:
    #     json.dump(targets, f, indent=2)

    draw(img0, x_scale, y_scale, results)
    if not os.path.exists('out'):
        os.makedirs('out')
    cv2.imwrite('out/yolo-output.jpg', img)

if __name__ == '__main__':
    run()

