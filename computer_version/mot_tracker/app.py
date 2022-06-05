import torch
from PIL import Image


# torch.hub.download_url_to_file(
#     'https://github.com/ultralytics/yolov5/raw/master/data/images/zidane.jpg', 'zidane.jpg')

img = Image.open('zidane.jpg')
scale = 640 / max(img.size)
img = img.resize((int(it * scale) for it in img.size), Image.ANTIALIAS)

model = torch.hub.load('ultralytics/yolov5', 'yolov5')

result = model(img)
result.render()

last = Image.fromarray(result.imgs[0])
