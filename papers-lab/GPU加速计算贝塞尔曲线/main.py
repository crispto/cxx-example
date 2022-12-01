"""
原始文章
https://www.hanspub.org/journal/PaperInformation.aspx?paperID=24275#f4
"""
#! /usr/bin/python3

import tkinter as tk

# 1. 统计控制顶点N的个数，采样点的个数，和每一次绘图的时间的关系

top =tk.Tk()
top.geometry("800x600")
c = tk.Canvas(top, bg='pink', height='600', width='800')


def on_click(event):
  x, y = event.x, event.y
  c.create_oval(x, y, x+10, y+10, fill='red')
  print("button 1 click")

c.bind('<ButtonPress-1>', on_click)
c.pack()

top.mainloop()
