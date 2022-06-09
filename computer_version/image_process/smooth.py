import cv2


def smooth(path, dim):
  """
  图片平滑
  """
  img = cv2.imread(path, flags='RGB')
  print(type(img))


if __name__ == "__main__":
  img_path= "../moon.jpeg"
  smooth(img_path, 8)