import onnx
import onnxruntime as rt
import numpy as np
import cv2
import matplotlib.pyplot as plt
import click
from utils import nice_colors


def getIou(box1, box2, inter_area):
    box1_area = box1[2] * box1[3]
    box2_area = box2[2] * box2[3]
    union = box1_area + box2_area - inter_area
    iou = inter_area / union
    return iou


def getInter(box1, box2):
    box1_x1, box1_y1, box1_x2, box1_y2 = box1[0] - box1[2] / 2, box1[1] - box1[3] / 2, \
        box1[0] + box1[2] / 2, box1[1] + box1[3] / 2
    box2_x1, box2_y1, box2_x2, box2_y2 = box2[0] - box2[2] / 2, box2[1] - box1[3] / 2, \
        box2[0] + box2[2] / 2, box2[1] + box2[3] / 2
    if box1_x1 > box2_x2 or box1_x2 < box2_x1:
        return 0
    if box1_y1 > box2_y2 or box1_y2 < box2_y1:
        return 0
    x_list = [box1_x1, box1_x2, box2_x1, box2_x2]
    x_list = np.sort(x_list)
    x_inter = x_list[2] - x_list[1]
    y_list = [box1_y1, box1_y2, box2_y1, box2_y2]
    y_list = np.sort(y_list)
    y_inter = y_list[2] - y_list[1]
    inter = x_inter * y_inter
    return inter

# onnx 输出的是 bbox 和 80 个类别的置信度，所以需要进行 NMS
from math import exp
def soft_nms(pred, conf_thres, iou_thres, sigma=0.4):
    """使用 soft nms 进行 NMS

    Args:
        pred (_type_): Onnx predict output [8400, 85], [x1, y1, x2, y2, max_conf, *all_conf]
        conf_thres (_type_): 小于该阈值的框被过滤
        iou_thres (_type_): 和 NMS 一样，IOU大于该阈值的框被过滤
        sigma: 衰减因子
    """
    pred = pred[np.where(pred[:, 4] > conf_thres)]
    conf_all = pred[:, 5:]
    label_result = np.argmax(conf_all, axis=-1)
    cls_all = list(set(label_result))
    pred = np.insert(pred, 5, label_result, axis=-1) # 将 label 插入到第5
    pred = pred[..., :6] # 后面的分数抛弃
    output_box = []
    for cls in cls_all:
      cls_box = cls[np.where(pred[:, 5] == cls)]
      select_box = []
      
      # 按得分大小排序
      sort_indics = np.argsort(cls_box[:, 4])
      cls_box = cls_box[sort_indics]
      # cls_box.sort(key=-1*cls_box[4])
      while len(cls_box):
        M = cls_box[0]
        select_box.append(M)
        cls_box = np.delete(cls_box, 0, axis=0)
        for i, remain in enumerate(cls_box):
          iou = getIou(M, remain, getInter(M, remain))
          remain[4] *= exp(-1 * iou ** 2 / sigma)
          if remain[4] < conf_thres:
            cls_box = np.delete(cls_box, i, axis=-1)
      return output_box   
            
        
        
      
    
    
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
def nms(pred, conf_thres, iou_thres):
    conf = pred[..., 4] > conf_thres  # 只处理最大置信度大于阈值的框
    box = pred[conf == True]
    cls_conf = box[..., 5:]  # 这些都是列别分数
    cls = []
    # 定位每个最大值的 index
    for i in range(len(cls_conf)):
        cls.append(int(np.argmax(cls_conf[i])))

    # 对每一种类别进行 NMS
    total_cls = list(set(cls))
    output_box = []
    for i in range(len(total_cls)):
        clss = total_cls[i]
        cls_box = []  # 候选框
        for j in range(len(cls)):
            if cls[j] == clss:
                box[j][5] = clss
                cls_box.append(box[j][:6])

        cls_box = np.array(cls_box)
        # sort by conf
        cls_box = cls_box[np.argsort(-cls_box[..., 4])]
        # box_conf = cls_box[..., 4]
        # box_conf_sort = np.argsort(box_conf)
        # max_conf_box = cls_box[box_conf_sort[len(box_conf) - 1]]
        max_conf_box = cls_box[0]
        output_box.append(max_conf_box)
        cls_box = np.delete(cls_box, 0, 0)

        while len(cls_box) > 0:
            # 刚刚插入的最大框
            max_conf_box = output_box[len(output_box) - 1]
            del_index = []
            for j in range(len(cls_box)):
                current_box = cls_box[j]
                interArea = getInter(max_conf_box, current_box)
                iou = getIou(max_conf_box, current_box, interArea)
                if iou > iou_thres:
                    del_index.append(j)
            cls_box = np.delete(cls_box, del_index, 0)
            if len(cls_box) > 0:
                output_box.append(cls_box[0])
                cls_box = np.delete(cls_box, 0, 0)
    return output_box


def draw(img, xscale, yscale, results, label2name):
    for box in results:
        pos = box[:4]
        # onnx 输出的是中心点坐标和宽高，需要转换成左上角和右下角坐标
        pos = [pos[0] - pos[2]/2, pos[1] - pos[3] /
               2, pos[0] + pos[2]/2, pos[1] + pos[3]/2]
        score = box[4]
        label = int(box[5])
        name = label2name[label]
        # print(f"{name}: {score}, {pos}, {pos2}, {label}")
        text = f"{name}: {score:.2f}"
        # draw rectrange and label with cv2
        font_size = 0.7
        lefttop = (int(pos[0]*xscale), int(pos[1]*yscale))
        rightbottom = (int(pos[2]*xscale), int(pos[3]*yscale))
        cv2.rectangle(img, lefttop, rightbottom, (0, 255, 0), 2)
        cv2.rectangle(img, lefttop, (lefttop[0]+len(text)*12,
                                     lefttop[1] - 14), nice_colors[len(nice_colors)-label-1], -1)
        cv2.putText(img, text, lefttop, cv2.FONT_HERSHEY_SIMPLEX,
                    font_size, (255, 255, 255), 2)


def get_class_map(model_path):
    """获取类别映射关系
    """
    import ast
    model = onnx.load(model_path)
    for meta in model.metadata_props:
        if meta.key == 'names':
            print(meta.value)
            classmap = ast.literal_eval(meta.value)
            return classmap


@click.command()
@click.argument('model_path', default='model/yolov8n.onnx')
@click.argument('image_path', default='data/crowd.jpeg')
def run(model_path, image_path):
    height, width = 640, 640
    img0 = cv2.imread(image_path)
    x_scale = img0.shape[1] / width
    y_scale = img0.shape[0] / height
    img = img0 / 255.
    img = cv2.resize(img, (width, height))
    img = np.transpose(img, (2, 0, 1))
    data = np.expand_dims(img, axis=0)
    # get meta

    label2name = get_class_map(model_path)
    print(f"label2name {label2name}")
    sess = rt.InferenceSession(model_path)
    input_name = sess.get_inputs()[0].name
    output_name = sess.get_outputs()[0].name

    print(f"input name: {input_name}, output name: {output_name}")
    pred = sess.run([output_name], {input_name: data.astype(np.float32)})[0]
    print(f"onnx output {pred.shape}")
    pred = np.squeeze(pred)  # 去掉 batch 维度
    pred = np.transpose(pred, (1, 0))

    # onnx 输出的是 bbox 和 80 个类别的置信度 [8400, 84]
    pred_class = pred[..., 4:]
    pred_conf = np.max(pred_class, axis=-1)
    # 将类别概率插入到原来的 pred 中，方便后面进行 NMS
    pred = np.insert(pred, 4, pred_conf, axis=-1)

    result = nms(pred, 0.3, 0.45)  # 进行 NMS
    print(f"result.shape: {len(result)}")
    ret_img = img0.copy()
    draw(ret_img, x_scale, y_scale, result, label2name)
    print("result is ", [re.tolist() for re in result])
    ret_img = ret_img[:, :, ::-1]  # turn BGR to RGB
    plt.imshow(ret_img)
    plt.show()


if __name__ == '__main__':
    run()