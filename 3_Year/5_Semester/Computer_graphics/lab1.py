import numpy as np
from pyglet.gl import *
from pyglet.window import Window
from pyglet import app
import sys

bg_color = [73, 103, 141]
border_color = [190, 173, 161]
circle_color = [145, 30, 66]

w = 200
vp = np.full((w, w, 3), bg_color, dtype = 'uint8')

for i in range(w//2):
    left, right = i - 2, i + 2
    vp[w//2 + left:w//2 + right, left:right] = border_color
    vp[w//2 - right:w//2 - left, left:right] = border_color
    vp[w - right - 1:w - left - 1, w//2 + left:w//2 + right] = border_color
    vp[left:right, w//2 + left: w//2 + right] = border_color

circle_points = 50
for i in range(circle_points):
    angle = 2*np.pi*i/circle_points
    x = lambda arg: int((arg-2) * np.cos(angle))
    y = lambda arg: int((arg - 2) * np.sin(angle))
    x_left, y_left = x(w//2) - 2, y(w//2) - 2
    x_right, y_right = x(w//2) + 2, y(w//2) + 2
    
    vp[y_left : y_right, x_left : x_right] = 255
    vp[w//2 + y_left : w//2 + y_right, w//2 + x_left : w//2 + x_right] = circle_color

vp = vp.flatten()
vp = (GLubyte * (w * w * 3))(*vp)

window = Window(visible = True, width = w, height = w, caption = 'VP')

@window.event
def on_key_press(symbol, modifiers):
    c = chr(symbol)
    if c == '1':
        app.exit()

@window.event
def on_draw():
    window.clear()
    glDrawPixels(w, w, GL_RGB, GL_UNSIGNED_BYTE, vp)
app.run()