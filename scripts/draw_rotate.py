from time import sleep
from math import cos, sin
from math import pi
import cv2
import numpy as np
# Video parameters
width, height = 640, 480  # Frame dimensions


# Create a window
cv2.namedWindow('Moving Box', cv2.WINDOW_NORMAL)
cv2.resizeWindow('Moving Box', width, height)


def rotate_point(x, y, rotate):
    """逆时针旋转一个点

    Args:
        x (_type_): _description_
        y (_type_): _description_
        rotate (_type_): _description_

    Returns:
        _type_: _description_
    """
    yaw = rotate / 180 * pi
    x_ro = cos(yaw) * x + sin(yaw) + y
    y_ro = -1 * sin(yaw) * x + cos(yaw) * y
    return (x_ro, y_ro)


def draw_roate_point(center):
    x, y = 100, 0
    for i in range(200):
        frame = np.ones((height, width, 3), np.uint8) * 255
        n_x, n_y = rotate_point(x, y, i * 5)  # 每次转 5度
        n_x, n_y = int(n_x), int(n_y)
        print("drawing ", (center[0] + n_x, center[1] + n_y))
        cv2.arrowedLine(
            frame, center, (center[0] + n_x, center[1] + n_y), (255, 0, 0), 2)
        cv2.putText(frame, f"degreee: {i*5}", (20, 40), 1, 1, (0, 0, 255), 1)
        cv2.imshow("Moving Box", frame)
        if cv2.waitKey(1000) & 0xFF == 27:  # Break the loop with the 'Esc' key
            break


def draw_one_car(frame, org, is_fusion, speed, speed_heading, car_size, car_heading):
    """绘制一辆车

    Args:
        frame (_type_): 背景
        org (_type_): 位置 (x, y)
        is_fusion (bool): 是否来自多个设备融合
        speed (_type_): 速度
        speed_heading (_type_): 速度朝向角
        car_size (_type_): 车身 (width, length, height)
        car_heading (_type_): 车身朝向角 (度)
    """
    pass


def draw_moving_box():
    """绘制一个移动的 box
    """
    # Box parameters
    box_width, box_height = 50, 50  # Box dimensions
    box_color = (0, 255, 0)  # Green color
    box_x = 0  # Initial x-coordinate of the box
    # Main loop to create the video
    fourcc = cv2.VideoWriter_fourcc(*'XVID')  # Codec
    fps = 30.0  # Frames per second
    out = cv2.VideoWriter('moving_box.avi', fourcc, fps, (width, height))
    while box_x <= width:
        frame = np.ones((height + 20, width + 200, 3), np.uint8) * 255

        cv2.rectangle(frame, (box_x, height // 2), (box_x + box_width,
                      height // 2 + box_height), box_color, -1)  # Draw a filled box
        out.write(frame)  # Write the frame to the video

        cv2.imshow('Moving Box', frame)
        if cv2.waitKey(30) & 0xFF == 27:  # Break the loop with the 'Esc' key
            break

        box_x += 5  # Move the box to the right

      # Release the video writer and close the window
    out.release()


draw_roate_point((width // 2, height // 2))

cv2.destroyAllWindows()
