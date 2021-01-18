import itertools
import pygame as pg
from pygame.locals import *
import music_player as mp
import chess
import time


BROWN = (165, 42, 42, 255)
WHITE = (255, 255, 255, 255)
RED = (255, 0, 0, 255)
BLACK = (0, 0, 0, 255)


class Player(object):
	def __init__(self, is_human):
		self.is_human = is_human
		if self.is_human != "human":
			self.init_ai()

	def init_ai(self):
		stockfish1 = "engine/stockfish_20090216_x64_avx2.exe"
		stockfish2 = "engine/stockfish.exe"
		deuterium = "engine/Deuterium.exe"
		cdrill = "engine/CDrill.exe"
		if self.is_human == "stockfish1":
			self.engine = chess.engine.SimpleEngine.popen_uci(stockfish1)
		elif self.is_human == "stockfish2":
			self.engine = chess.engine.SimpleEngine.popen_uci(stockfish2)
		elif self.is_human == "deuterium":
			self.engine = chess.engine.SimpleEngine.popen_uci(deuterium)
		elif self.is_human == "cdrill":
			self.engine = chess.engine.SimpleEngine.popen_uci(cdrill)
		else:
			print(f"couldn't load {self.is_human}, loading 'human' as default")
			self.is_human = "human"


class ChessGame:
	def __init__(self):
		self.init_pygame()
		self.init_chessboard_surface(40)
		self.board = chess.Board()
		self.new_game()
		self.music = mp.MusicPlayer(20, 130)

	def init_pygame(self):
		pg.init()
		icon_surface = pg.image.load('assets/icon.ico')
		pg.display.set_icon(icon_surface)
		pg.display.set_caption("Avoc Chess")
		self.screen = pg.display.set_mode((800, 600), HWSURFACE | DOUBLEBUF | RESIZABLE)
		self.fonts = self.load_fonts("assets/Inconsolata-Bold.ttf", 1, 30)

	def load_fonts(self, path, minsize, maxsize):
		fonts = []
		i = minsize
		while i < maxsize:
			fonts.append(pg.font.Font(path, i))
			i += 1
		return fonts

	def init_chessboard_surface(self, tile_size, border=5, border_color=BLACK):
		self.chessboard_border = border
		self.chessboard_title_size = tile_size
		colors = itertools.cycle((WHITE, BROWN))
		tile_size = tile_size
		width, height = 8*tile_size, 8 * tile_size
		self.chessboard_surface = pg.Surface((width + 2 * border, height + 2 * border))
		self.chessboard_surface.fill(border_color)
		pg.draw.rect(self.chessboard_surface, WHITE, pg.Rect(border, border, width, height))
		for y in range(0, height, tile_size):
			for x in range(0, width, tile_size):
				rect = (x + border, y + border, tile_size, tile_size)
				pg.draw.rect(self.chessboard_surface, next(colors), rect)
				if x == 0:
					number_txt = self.fonts[14].render(str(int(8 - y / tile_size)), True, next(colors))
					self.chessboard_surface.blit(number_txt, (border, border + y))
					next(colors)
				if y == height - tile_size:
					letter_txt = self.fonts[14].render(chr(ord("a") + int(x / tile_size)), True, next(colors))
					pos_x = border + x + tile_size - letter_txt.get_size()[0]
					pos_y = border + y + tile_size- letter_txt.get_size()[1]
					self.chessboard_surface.blit(letter_txt, (pos_x, pos_y))
					next(colors)
			next(colors)

	def new_game(self, p1="human", p2="human"):
		self.board.reset()
		self.get_chessboard_from_board()
		self.movehistory = []
		self.p1 = Player(p1)
		self.p2 = Player(p2)

	def get_chessboard_from_board(self):
		self.board_tab = 	[["1", "1", "1", "1", "1", "1", "1", "1"],
							["1", "1", "1", "1", "1", "1", "1", "1"],
							["1", "1", "1", "1", "1", "1", "1", "1"],
							["1", "1", "1", "1", "1", "1", "1", "1"],
							["1", "1", "1", "1", "1", "1", "1", "1"],
							["1", "1", "1", "1", "1", "1", "1", "1"],
							["1", "1", "1", "1", "1", "1", "1", "1"],
							["1", "1", "1", "1", "1", "1", "1", "1"]]
		fen = self.board.fen().split(' ')[0].split('/')
		tab_y = 0
		for line in fen:
			tab_x = 0
			for car in line:
				try:
					tab_x += int(car)
				except:
					self.board_tab[tab_y][tab_x] = car
					tab_x += 1
			tab_y += 1
		self.chessboard_surface_actual = pg.Surface.copy(self.chessboard_surface)
		y = 0
		while y < 8:
			x = 0
			while x < 8:
				if self.board_tab[y][x] != "1":
					txt = self.fonts[20].render(self.board_tab[y][x], True, BLACK)
					pos_x = self.chessboard_border + x * self.chessboard_title_size + self.chessboard_title_size / 2 - txt.get_size()[0] / 2
					pos_y = self.chessboard_border + y * self.chessboard_title_size + self.chessboard_title_size / 2 - txt.get_size()[1] / 2
					self.chessboard_surface_actual.blit(txt, (pos_x, pos_y))
				x += 1
			y += 1

	def display(self):
		self.screen.fill((60, 70, 90))
		self.screen.blit(self.chessboard_surface_actual, (20, 140))
		self.music.display(self.screen, 20, 20)
		pg.display.flip()
		

chess_game = ChessGame()
clock = pg.time.Clock()
game_exit = False
while not game_exit:

	for event in pg.event.get():
		if event.type == pg.QUIT:
			game_exit = True
		if not chess_game.music.event(event):
			if event.type == pg.MOUSEBUTTONDOWN:
				if event.button == 1:
					pass
	chess_game.display()
	clock.tick(60)

pg.quit()
