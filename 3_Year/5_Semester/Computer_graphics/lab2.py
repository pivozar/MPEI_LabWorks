from pyglet.gl import *
from pyglet import app, graphics
from pyglet.window import Window, key
import numpy as np

bg_color = [73, 103, 141]
border_color = [190, 173, 161]
circle_color = [145, 30, 66]

dx, dy = 25, 15 
dx2 = dx / 2
dy2 = dy / 2
wx, wy = 1.5 * dx2, 1.5 * dy2 
width, height = int(20 * wx), int(20 * wy)
window = Window(visible = True, width = width, height = height,
                resizable = True, caption = 'ЛР_02')
glClearColor(0, 0, 0, 1.0)
glClear(GL_COLOR_BUFFER_BIT)
glEnable(GL_POINT_SMOOTH)
glPointSize(15)

pattern = int(0b1111000011110000)
sw = 0
sw1 = 0
sw2 = 0
sw3 = 0
sw5 = 0

@window.event
def on_draw():
    window.clear()
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-wx, wx, -wy, wy, -1, 1)

    glLineWidth(2)
    glColor3f(1,1,1) 
    glPolygonMode(GL_FRONT, GL_FILL)
    glPolygonMode(GL_BACK, GL_LINE)
    glEnable(GL_LINE_STIPPLE)
    glLineStipple(3, pattern)

    glBegin(GL_LINES)
    glVertex3f(0,-height//2,0)
    glVertex3f(0,height//2,0)
    glVertex3f(-width//2,0,0)
    glVertex3f(width//2,0,0)
    glEnd()
    glDisable(GL_LINE_STIPPLE)
    
    glBegin(GL_LINE_LOOP)
    n_points = 100
    a, b = 14, 7
    for i in range(n_points):
        angle = 2*np.pi*i/n_points
        r = a*b/(a**2 * np.sin(angle)**2 + b**2 * np.cos(angle)**2)**0.5
        x = r * np.cos(angle)
        y = r * np.sin(angle)
        glVertex3f(x, y, 0)
    glEnd()

    glRotatef(180*sw5,1,0,0)

    graphics.draw(3, GL_TRIANGLES,
                          ('v2f', (-a, 0, a, 0, 0, b)),
                          ('c3f', (1, 0, 0, 0, 1, 0, 0, 0, 1)))
    
    glBegin(GL_QUADS)
    glColor3f(0, 1, 0)
    glVertex3f(-a, b, 0)
    glColor3f(1, 0, 1)
    glVertex3f(a, b, 0)
    glColor3f(0, 1, 1)
    glVertex3f(a, -b, 0)
    glColor3f(1, 1, 0)
    glVertex3f(-a, -b, 0)
    glEnd()
    

    glBegin(GL_POINTS)
    glColor3f(145/255, 30/255, 66/255)
    glVertex3f(0, 0, 0)
    glEnd()
    
@window.event
def on_key_press(symbol, modifiers):
    global sw, sw1, sw2, sw3, sw5, pattern
    if symbol == key._1:
        sw = 1 - sw
    elif symbol == key._2:
        sw1 = 1 - sw1
    elif symbol == key._3:
        sw2 = 1 - sw2
    elif symbol == key._4:
        sw3 = 1 - sw3
    elif symbol == key._5:
        sw5 = 1 - sw5
    elif symbol == key._6:
        sw = 0
        sw1 = 0
        sw2 = 0
        sw3 = 0
        sw5 = 0
    if sw == 0:
        pattern = int(0b1111000011110000)
    else:
        pattern = int(0b1111111111111111)
    if sw1 == 0:
        glShadeModel(GL_SMOOTH)
    else:
        glShadeModel(GL_FLAT)
    if sw2 == 0:
        glFrontFace(GL_CCW)
    else:
        glFrontFace(GL_CW)
    if sw3 == 0:
        glEnable(GL_POINT_SMOOTH)
    else:
        glDisable(GL_POINT_SMOOTH)

app.run()