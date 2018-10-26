import pygame as pg
from math import sin,cos
pg.init()
w=500
h=500
screen = pg.display.set_mode((w,h))
pg.display.set_caption('SFML is shit')

crashed = False

def kolo(x,y,r,br):
    x,y,r,br=map(int, [x,y,r,br])
    pg.draw.circle(screen, (br, br, br), (x,y), r)

def obrazek(a):
    for i in range(200, w*6//7):
        kolo(i, (h/2+sin(10*i/w)*h/2)*0.5 + h/4, abs(sin(a*0.2)*w/2 + w/2 - i )/10+3, abs(cos(a*i/w))*255);

a=1
while not crashed:
    a+=0.1
    for event in pg.event.get():
        if event.type == pg.QUIT:
            crashed = True
    screen.fill((0,0,0))
    obrazek(a)
    pg.display.update()
