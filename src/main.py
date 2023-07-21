import pygame
from pygame._sdl2.video import Window, Renderer, Texture, Image
import sys
from engine import *
from settings import *


pygame.init()
clock = pygame.time.Clock()
font_billy_regular = pygame.font.Font("assets/billy/Billy-Regular.ttf", 20)


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
    self.x_vel = 2
    self.y_vel = 2
    self.anim = 0
    self.texs, self.rects = load_tex('assets/player-run.png', win.renderer, 8, 3)
    self.should_move = False

  def update(self):
    self.base_update(win, self.x_pos, self.y_pos, True)
    if self.should_move:
      self.wasd(self.x_vel, self.y_vel)


class Menu(Entity):
  def __init__(self):
    self.x_pos = -440
    self.y_pos = 0
    self.x_vel = 0.1
    self.tex, self.rect = load_tex('assets/menu-wall.png', win.renderer, 1, 0.75)

  def update(self):
    self.x_pos += self.x_vel
    self.base_update(win, self.x_pos, self.y_pos, False)

game = Game()
win = WindowHandler((WIN_WIDTH, WIN_HEIGHT), 1)
menu = Menu()
corbin = Corbin()
grass_1 = Block((0, 0), "grass-1", win)

menu_buttons = {
  "Play": "gameplay",
  "Settings": "settings"
}

def add_buttons():
  for i, key in enumerate(menu_buttons):
    value = list(menu_buttons.values())[i]
    menu_buttons[key] = LinkButton(key, (win.width/15, win.height/2 + 24*i), 2*(font_sizes["subtitle"],), font_billy_regular, (255, 255, 255, 255), win.renderer, lambda: set_state(game, value))

add_buttons()

while game.running:
  for event in pygame.event.get():
    for menu_button in menu_buttons:
      menu_buttons[menu_button].process_event(event)
    if event.type == pygame.QUIT:
      quit(game.running)

  fill_rect(win.renderer, (0, 0, *win.size), (0, 0, 0, 255))

  if game.state == "menu":
    menu.update()
    for menu_button in menu_buttons:
      menu_buttons[menu_button].update(win)

  if game.state == "gameplay":
    grass_1.update(win, (corbin.x_vel, corbin.y_vel))
    corbin.update()

  win.renderer.present()
