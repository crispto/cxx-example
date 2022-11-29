from torchvision import models

from torchvision import transforms
from PIL import Image
import torch 


preprocess = transforms.Compose([transforms.Resize(256),
                                 transforms.CenterCrop(244),
                                 transforms.ToTensor()
                                 ])

img = Image.open("./data/dog.jpg")
# img.show()
img_t = preprocess(img)
print(img_t.size())
batch_t = torch.unsqueeze(img_t, 0)
print(batch_t.size())

resnet = models.resnet101(pretrained=True)

resnet.eval()
out = resnet(batch_t)
print(out.size())
per = torch.nn.functional.softmax(out, dim=1)[0] *100
print(per)
