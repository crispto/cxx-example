from andro_wrap import *

def main():
  v = "{\"x\": 12, \"y\": 13}"
  print("v is {}".format(v))
  param = create_center2(v)
  print("param ptr is 0x{}".format(param))
  show2()

  print("-----------add point")
  p1 = {"x": 1, "y":2}
  p2 = {"x": 1, "y":2}
  p3 = add_point2(p1, p2)
  print("p3 {}, {}".format(p3.x, p3.y))

  print("------ cvt ")
  ps = cvt_point2(param, [p3, p3, p3])
  for px in ps:
    print("x: {}, y: {}".format(px.x, px.y))
  
  free_center(param)
  show2()


if __name__ == "__main__":
  main()