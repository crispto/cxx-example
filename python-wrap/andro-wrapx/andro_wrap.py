# from andro import create_center, show
from andro import *



def create_center2(cfg):
  return create_center(cfg)

def add_point2(p1, p2):
  out = (point_t)()
  p1p = point_t()
  p2p = point_t()

  for name in p1:
    setattr(p1p, name, p1[name])

  for name in p2:
    setattr(p2p, name, p1[name])

  add_point(p1p, p2p, out)
  return out

def show2():
  show()

point_p = POINTER(None)
def cvt_point2(param, ps):
  ps_num = len(ps)
  out = POINTER(point_t)()
  ps_in = (point_t * ps_num)(*ps)
  cvt_point(param, ps_in, ps_num, out)
  return out[:ps_num]

def free_center2(pr):
  free_center(pr)
    
