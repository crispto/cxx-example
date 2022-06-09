def start():
    enter()


def enter():
    print("enter exe...")
    enter_to_enter()


def enter_to_enter():
    print("enter to enter exe...")
    a = 1/0


"""
python 的 traceback 是从上到下的调用栈，因此看最底部就是触发错误的地方
"""


class Callable:
    def __call__(self, name, parm):
        print("name: {}, param: {}".format(name, parm))


a = Callable()

a("yang", "good")
