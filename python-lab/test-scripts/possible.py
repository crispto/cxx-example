"""
两个骰子，计算和的概率分布函数
"""

def get_pos(n):
    if n < 2 or 12 <n :
        return 0
    c = 0
    for i in range(1, 7):
        if 0< n - i and n-i <7:
            c+=1
    return c

v=  []
for x in range(2, 13):
    v.append(get_pos(x))

print(v)
print(sum(v))