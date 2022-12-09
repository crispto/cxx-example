import sys
import os
from re import compile
sys.path.append("/Users/richardyang/coding/github/laboratory/python-lab")
# from imgutils.show import crop_img
from imgutils.dirutil import find_by_ext

def main():
    root = "/Users/richardyang/coding/github/laboratory"
    exts = ['py', 'cpp', 'json']
    excludes = [r'^.vscode.*', 'build', 'install', r'.*dSYM']
    pattern = [compile(x) for x in excludes]

    ret = find_by_ext(root, pattern, exts)
    print("totally find %d results\n" % len(ret))
    with open("out.txt", 'w') as f:
        for x in ret:
            f.write(x+"\n")
    


if __name__ == "__main__":
    main()
