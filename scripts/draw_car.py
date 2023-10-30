from math import cos, sin
from math import pi
import cv2
import numpy as np
# from .color import GREEN, YELLOW, ORANGE, RED, BLUE


RED = (0, 0, 255)
GREEN = (0, 255, 0)
BLUE = (255, 0, 0)
YELLOW = (0, 255, 255)
CYAN = (255, 255, 0)
MAGENTA = (255, 0, 255)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (128, 128, 128)
LIGHT_GRAY = (192, 192, 192)
DARK_GRAY = (64, 64, 64)
ORANGE = (0, 165, 255)


def format_rt_mat(rotate, trans):
    """构建旋转平移矩阵

    Args:
        rotate (float): 弧度
        trans (_type_): 平移矩阵
    """
    return np.array([[cos(rotate), -1 * sin(rotate), 0],
                    [sin(rotate), cos(rotate), 0],
                    [trans[0], trans[1], 1]])


def decide_color(speed):
    if speed < 10:
        return GREEN
    elif speed < 20:
        return YELLOW
    elif speed < 50:  # 180km/h
        return ORANGE
    return RED  # wrong number


def draw_one_car(frame, pos, is_fusion, speed, speed_heading, car_size, car_heading):
    """绘制一辆车

    Args:
        frame (_type_): 背景
        pos (_type_): 位置 (x, y)
        is_fusion (bool): 是否来自多个设备融合
        speed (_type_): 速度
        speed_heading (_type_): 速度朝向角
        car_size (_type_): 车身 (width, length, height)
        car_heading (_type_): 车身朝向角 (度)
    """
    speed_scale = 10
    speed_end = round(speed * speed_scale)
    width, length, _ = car_size
    car_head_marker_length = 10  # 车头保险杠
    # 原点出的四个角
    # 中心 -> 速度末尾
    car_body_points = np.array([[length / 2, width / 2], [length / 2, - width / 2],
                               [-length / 2, width / 2], [-length / 2, -width / 2],
                               [0, 0], [speed_end, 0], [length / 2 - car_head_marker_length, width / 2], [length / 2 - car_head_marker_length, -width / 2]])
    # 旋转平移后真实的绘制地址
    tmp_car_body_points = np.hstack(
        [car_body_points, np.full((car_body_points.shape[0], 1), 1)])
    car_rotate_mat = format_rt_mat(car_heading, pos)
    draw_car_points = (
        (car_rotate_mat.T @ tmp_car_body_points.T).T).astype(int)

    print(f"draw_car_points shape: {draw_car_points.shape}")
    # 将点连起来
    to_connect = [[0, 1], [1, 3], [3, 2], [2, 0], [6, 7]]
    for line_index in to_connect:
        p1 = draw_car_points[line_index[0]][:2].tolist()
        p2 = draw_car_points[line_index[1]][:2].tolist()
        cv2.line(frame, p1, p2, BLUE, 2)

    # 画速度线
    p1 = draw_car_points[4][:2].tolist()  # 车中心
    p2 = draw_car_points[5][:2].tolist()  # 速度 end
    cv2.arrowedLine(frame, p1, p2, decide_color(speed), 2)


def draw_moving_car(frame_shape):
    """绘制一辆移动的汽车

    """
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    out = cv2.VideoWriter("moving car.avi", fourcc, 30, frame_shape)
    start_pos = (200, 200)
    start_heading = 0
    rotate_speed = 1  # 5度
    speed = 1
    car_size = [24, 50, 0]

    for i in range(1000):
        background = np.full(
            (frame_shape[0], frame_shape[1], 3), 255, np.uint8)
        current_pos = [start_pos[0] + speed * i, start_pos[1] + speed * i]
        current_heading = (start_heading + rotate_speed * i) / pi

        # 画一辆车
        draw_one_car(background, current_pos, False, 5,
                     0, car_size, current_heading)
        out.write(background)
        cv2.imshow("CAR", background)
        if cv2.waitKey(100) == ord('q'):
            break


if __name__ == "__main__":
    # Video parameters
    width, height = 640, 480  # Frame dimensions

    # Create a window
    cv2.namedWindow('CAR', cv2.WINDOW_NORMAL)
    cv2.resizeWindow('CAR', width, height)
    draw_moving_car((width, height))
    cv2.destroyAllWindows()
