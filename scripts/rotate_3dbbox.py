import numpy as np
from math import cos, sin
import cv2


def rotate_3d_bbox(bbox, yaw, pitch, roll):
    """
    Rotates a 3D bounding box.

    Args:
        bbox (list): The 3D bounding box to rotate. It should be a list of 8 points, each point being a list of 3 coordinates.
        yaw (float): The yaw angle in radians.
        pitch (float): The pitch angle in radians.
        roll (float): The roll angle in radians.

    Returns:
        list: The rotated 3D bounding box.
    """
    # Create the rotation matrix
    R_yaw = np.array([
        [cos(yaw), -sin(yaw), 0],
        [sin(yaw), cos(yaw), 0],
        [0, 0, 1]
    ])
    R_pitch = np.array([
        [cos(pitch), 0, sin(pitch)],
        [0, 1, 0],
        [-sin(pitch), 0, cos(pitch)]
    ])
    R_roll = np.array([
        [1, 0, 0],
        [0, cos(roll), -sin(roll)],
        [0, sin(roll), cos(roll)]
    ])
    R = np.dot(R_yaw, np.dot(R_pitch, R_roll))

    # Apply the rotation to each point in the bounding box
    bbox_rotated = [np.dot(R, point) for point in bbox]

    return bbox_rotated

# I want the 3d bbox project to 2d pixel in a good observe degree


def project_3dbbox_to_2d(bbox, yaw, pitch, roll):
    """
    # Create the rotation matrix
    """
    R_yaw = np.array([
        [cos(yaw), -sin(yaw), 0],
        [sin(yaw), cos(yaw), 0],
        [0, 0, 1]
    ])
    R_pitch = np.array([
        [cos(pitch), 0, sin(pitch)],
        [0, 1, 0],
        [-sin(pitch), 0, cos(pitch)]
    ])
    R_roll = np.array([
        [1, 0, 0],
        [0, cos(roll), -sin(roll)],
        [0, sin(roll), cos(roll)]
    ])
    R = np.dot(R_yaw, np.dot(R_pitch, R_roll))

    # Apply the rotation to each point in the bounding box
    bbox_rotated = [np.dot(R, point) for point in bbox]
    bbox_rotated = np.array(bbox_rotated)
    bbox_rotated = bbox_rotated[:, :2]
    return bbox_rotated


def main():
    bbox = [
        [0, 0, 0],
        [1, 0, 0],
        [1, 1, 0],
        [0, 1, 0],
        [0, 0, 1],
        [1, 0, 1],
        [1, 1, 1],
        [0, 1, 1]
    ]
    bbox = np.array(bbox)
    bbox *= 60
    bbox += 400
    print(bbox)
    # now i want bbox rotate 5 degree a second in a while loop, and visuialize it with opencv
    yaw = 0
    pitch = 0
    roll = 0
    while True:
        bbox_rotated = rotate_3d_bbox(bbox, yaw, pitch, roll)
        bbox_rotated = np.array(bbox_rotated).astype(np.int32)
        img = np.zeros((800, 800))
        project2d = project_3dbbox_to_2d(bbox_rotated, yaw, roll, pitch)
        project2d = project2d.astype(np.int32)
        img = cv2.polylines(img, [project2d[:4]], True, (255, 255, 255), 2)
        print("get ", project2d[:4])

        img = cv2.polylines(img, [project2d[4:]], True, (255, 255, 255), 2)

        q1 = np.array([project2d[4], project2d[7],
                       project2d[3], project2d[0]])
        print("get ", q1)

        img = cv2.polylines(img, [q1], True, (255, 255, 255), 2)
        q2 = np.array([project2d[1], project2d[2],
                       project2d[6], project2d[5]])

        img = cv2.polylines(img, [q2], True, (255, 255, 255), 2)
        cv2.imshow("image", img)
        if cv2.waitKey(100) == ord('q'):
            break
        yaw += 0.1
        pitch += 0.1
        roll += 0.1


if __name__ == "__main__":
    main()
