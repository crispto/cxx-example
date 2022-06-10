import cv2
import numpy as np
import coloredlogs
import logging


def smooth(path, dim):
    """
    图片平滑
    """
    img = cv2.imread(path, 0)
    print('width: ', img.shape, img.size)
    cv2.imshow('image', img)
    height, width = img.shape
    img2 = np.zeros((height, width))
    for i in range(height):
        for j in range(width):
            pt = width * i + j
            # numpy 矩阵使用 itemset 来写值， item 获得值
            # make every pixle value to a matrix of the dim * dim

    cv2.imshow('img2', img2)
    cv2.waitKey(0)


if __name__ == "__main__":
    import os

    logger = logging.getLogger(__name__)
    coloredlogs.install(level='DEBUG')

    logger.debug('current path: %s ', os.getcwd())
    img_path = "../moon.jpeg"
    smooth(img_path, 8)
