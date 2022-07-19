from common import *
from common import _libs

from ctypes import *
senseauto_hdl = POINTER(None)
class struct_point_t(Structure):
    pass
struct_point_t.__slots__ = [
    'x',
    'y'
]
struct_point_t._fields_ = [
    ('x', c_int32),
    ('y', c_int32)
]
point_t = struct_point_t



for _lib in _libs.values():
    if not _lib.has("create_center", "cdecl"):
        continue
    create_center = _lib.get("create_center", "cdecl")
    create_center.argtypes = [String]
    create_center.restype = c_void_p
    break

for _lib in _libs.values():
    if not _lib.has("free_center", "cdecl"):
        continue
    free_center = _lib.get("free_center", "cdecl")
    free_center.argtypes = [c_void_p]
    free_center.restype = None
    break

for _lib in _libs.values():
    if not _lib.has("show", "cdecl"):
        continue
    show = _lib.get("show", "cdecl")
    show.argtypes = []
    show.restype = None
    break

for _lib in _libs.values():
    if not _lib.has("add_point", "cdecl"):
        continue
    add_point = _lib.get("add_point", "cdecl")
    add_point.argtypes = [point_t, point_t, POINTER(point_t)]
    add_point.restype = c_int32
    break

for _lib in _libs.values():
    if not _lib.has("cvt_point", "cdecl"):
        continue
    cvt_point = _lib.get("cvt_point", "cdecl")
    cvt_point.argtypes = [POINTER(None), POINTER(point_t), c_int32, POINTER(POINTER(point_t))]
    cvt_point.restype = c_int32
    break