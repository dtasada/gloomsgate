import pygame
from pygame._sdl2.video import Window, Renderer, Texture, Image
from engine import *
from settings import *
from sys import exit

pygame.init()
clock = pygame.time.Clock()
font = pygame

class WindowHandler:
    def __init__(self, size, vsync=0):
        self.window = Window(title="Gloomsgate", size=size)
        self.window.resizable = True
        self.renderer = Renderer(self.window, vsync=vsync)
        self.size = size
        self.width, self.height = self.size
        self.center = [s // 2 for s in size]

class Corbin(Entity):
    def __init__(self):
        self.x_pos = win.center[0]
        self.y_pos = win.center[1]
        self.anim = 0
        self.textures, self.rectangles = load_texture('../assets/player_run.png', win.renderer, 8)
    def update(self):
        self.base_update(win)

win = WindowHandler((WIN_WIDTH, WIN_HEIGHT), 1)
corbin = Corbin()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()

    corbin.update()
    win.renderer.present()
