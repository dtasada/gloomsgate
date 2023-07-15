import pygame
from pygame._sdl2.video import Window, Renderer, Texture, Image

def load_texture(path, renderer, frames=1):
    if frames > 1:
        surface = pygame.image.load(path)
        frame_width = surface.get_width() / frames
        frame_height = surface.get_height()
        textures = [Texture.from_surface(renderer, surface.subsurface(x * frame_width, 0, frame_width, frame_height)) for x in range(frames)]
        rectangles = [tex.get_rect(midbottom = (50, 50)) for tex in textures]
        return textures, rectangles
    else:
        surface = pygame.image.load(path)
        texture = Texture.from_surface(renderer, surface)
        rectangle = texture.get_rect(midbottom = (50, 50))
        return texture, rectangle

class Entity():
    def animate(self, textures, rectangles, frequency):
        self.anim += frequency
        if self.anim >= len(rectangles):
            self.anim = 0
        self.texture = textures[int(self.anim)]
        self.rectangle = rectangles[int(self.anim)]

    def base_update(self, win):
        self.animate(self.textures, self.rectangles, 0.1)
        win.renderer.blit(self.texture, self.rectangle)
