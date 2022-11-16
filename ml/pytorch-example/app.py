from torchvision import models

from torchvision import transforms
preprocess = transforms.Compose([transforms.Resize(256),
                                 transforms.CenterCrop(244),
                                 transforms.ToTensor()
                                 ])
from PIL import Image

img = Image.open("./data/walk.jpg")
# img.show()

img_t = preprocess(img)
import torch 
batch_t = torch.unsqueeze(img_t, 0)