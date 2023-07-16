import pygame
from pygame._sdl2.video import Window, Renderer, Texture, Image
import sys
from engine import *
from settings import *


pygame.init()
clock = pygame.time.Clock()
font_billy_regular = pygame.font.Font("../assets/billy/Billy-Regular.ttf", 20)


class Game():
  def __init__(self):
    self.state = "menu"
    self.running = True

class WindowHandler:
  def __init__(self, size, vsync=0):
    self.window = Window(title="Gloomsgate", size=(size[0]*SCALE_CONST, size[1]*SCALE_CONST))
    self.window.resizable = True
    self.renderer = Renderer(self.window, vsync=vsync)
    self.size = size
    self.width, self.height = self.size
    self.center = [s // 2 for s in size]
    self.renderer.scale = (SCALE_CONST, SCALE_CONST)


class Corbin(Entity):
  def __init__(self):
    self.x_pos = win.center[0]
    self.y_pos = win.center[1]
    self.anim = 0
    self.texs, self.rects = load_tex('../assets/player-run.png', win.renderer, 8)

  def movement(self):
    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
      self.y_pos -= 2
    if keys[pygame.K_a]:
      self.x_pos -= 2
    if keys[pygame.K_s]:
      self.y_pos += 2
    if keys[pygame.K_d]:
      self.x_pos += 2

  def update(self):
    self.base_update(win, self.x_pos, self.y_pos)
    self.movement()

class Menu(Entity):
  def __init__(self):
    self.x_pos = -440
    self.y_pos = 0
    self.tex, self.rect = load_tex('../assets/menu-wall.png', win.renderer, 1, 0.75)

  def update(self):
    self.x_pos += 0.1
    self.base_update(win, self.x_pos, self.y_pos, False)


game = Game()
win = WindowHandler((WIN_WIDTH, WIN_HEIGHT), 1)
menu = Menu()
corbin = Corbin()

menu_buttons = [LinkButton("Play", (win.width/15, win.height/2), (24, 24), font_billy_regular, (255, 255, 255, 255), win.renderer, lambda: set_state(game, "gameplay"))]

while game.running:
  for event in pygame.event.get():
    for menu_button in menu_buttons:
      menu_button.process_event(event)
    if event.type == pygame.QUIT:
      quit(game.running)

  fill_rect(win.renderer, (0, 0, *win.size), (0, 0, 0, 255))

  if game.state == "menu":
    menu.update()
    for menu_button in menu_buttons:
      menu_button.update(win)

  if game.state == "gameplay":
    corbin.update()

  win.renderer.present()
