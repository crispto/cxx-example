import os
from os import path

def _in_exclude_pat(sub_path, excludes_pattern):
    for pat in excludes_pattern:
        if pat.match(path.basename(sub_path)):
            print("%s match %s\n"%(sub_path, str(pat)))
            return True
    return False


def _find_by_ext(root, exts, excludes_pattern, out):
    # print("searching %s \n" % root)
    for sub_path in os.listdir(root):
        sub_path = path.join(root, sub_path)
        if os.path.isdir(sub_path):
            if _in_exclude_pat(sub_path, excludes_pattern):
                # print("filted file %s\n" % sub_path)
                continue
            _find_by_ext(sub_path, exts, excludes_pattern, out)
        elif os.path.isfile(sub_path):
            ext = path.basename(sub_path).split(".")[-1]
            if ext in exts:
                out.append(sub_path)


def find_by_ext(root: str, exclude: list, ext_list: list) -> list:
    """
    find by ext_list
    """
    out = list()
    _find_by_ext(root, ext_list, exclude, out)
    return out
