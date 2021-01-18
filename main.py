import chess.svg
import chess.pgn
import chess.engine
from IPython.display import SVG
# https://medium.com/dscvitpune/lets-create-a-chess-ai-8542a12afef

count = 0
movehistory = []
game = chess.pgn.Game()
board = chess.Board()
stockfish1 = "engine/stockfish_20090216_x64_avx2.exe"
stockfish2 = "engine/stockfish.exe"
deuterium = "engine/Deuterium.exe"
cdrill = "engine/CDrill.exe"
engine = chess.engine.SimpleEngine.popen_uci(deuterium)
fen = board.fen().split(' ')[0].split('/')
print(fen)
while not board.is_game_over(claim_draw=True):
	if board.turn:
		count += 1
		print(f'\n{count}\n')
		move = engine.play(board, chess.engine.Limit(time=0.1))
		movehistory.append(move.move)
		board.push(move.move)
		print(board)
		fen = board.fen().split(' ')[0].split('/')
		print(fen)
	else:
		human_move = input()
		board.push_san(human_move)
		print(board)
		fen = board.fen().split(' ')[0].split('/')
		print(fen)
		

game.add_line(movehistory)
game.headers["Result"] = str(board.result(claim_draw=True))
print(game)
SVG(chess.svg.board(board=board, size=400))
