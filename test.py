import itertools
import pygame as pg
import music_player as mp

WHITE = (255, 255, 255)

class Chess:
	def __init__(self):
		self.init_pygame()
		self.init_chessboard_surface(40)
		self.music = mp.MusicPlayer(20, 130)
		
	def init_pygame(self):
		pg.init()
		icon_surface = pg.image.load('assets/icon.ico')
		pg.display.set_icon(icon_surface)
		pg.display.set_caption("Avoc Chess")
		self.screen = pg.display.set_mode((800, 600))

	def init_chessboard_surface(self, tile_size):
		BLACK = pg.Color('brown')
		WHITE = pg.Color('white')
		colors = itertools.cycle((WHITE, BLACK))
		tile_size = tile_size
		width, height = 8*tile_size, 8*tile_size
		self.chessboard_surface = pg.Surface((width, height))
		self.chessboard_surface.fill(WHITE)
		for y in range(0, height, tile_size):
			for x in range(0, width, tile_size):
				rect = (x, y, tile_size, tile_size)
				pg.draw.rect(self.chessboard_surface, next(colors), rect)
			next(colors)

	def display(self):
		self.screen.fill((60, 70, 90))
		self.screen.blit(self.chessboard_surface, (30, 140))
		self.music.display(self.screen, 20, 20)
		pg.display.flip()

chess = Chess()
clock = pg.time.Clock()
game_exit = False
while not game_exit:

	for event in pg.event.get():
		if event.type == pg.QUIT:
			game_exit = True
		if not chess.music.event(event):
			if event.type == pg.MOUSEBUTTONDOWN:
				if event.button == 1:
					pass
	chess.display()
	clock.tick(60)

pg.quit()
