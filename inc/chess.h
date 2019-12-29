#ifndef CHESS_H
 #define CHESS_H

#include "ft_printf.h"
#include <time.h>
#include <SDL.h>
#include "SDL_image.h"

#define WHITE 255, 255, 255
#define DARK 0, 0, 0
#define BROWN 150 ,75 ,0
#define RED 255, 0, 0
#define HIST_MAX 50
#define RBACK_X 50 + 8 * 60 + 50
#define RBACK_Y 50 + 4 * 60
#define RBACK_W 60
#define RBACK_H 60

typedef	struct 		s_rock
{
	_Bool			p1l;
	_Bool			p1r;
	_Bool			p2l;
	_Bool			p2r;
}					t_rock;

typedef	struct 		s_piece
{
	char			color;
	char			type;
	size_t			pos_x;
	size_t			pos_y;
	SDL_Rect		rect;
}					t_piece;

typedef	struct 		s_game_state
{
	t_piece			board[64];
	t_rock			rock;
	char			turn;
}					t_game_state;

typedef	struct 		s_predic
{
	SDL_Rect		rect[64];
	size_t			nb;
	t_game_state	game_s[64];
	SDL_Rect		target;
}					t_predic;

typedef	struct 		s_player
{
	_Bool			human;
	char			color;
	size_t			number;
}					t_player;

void			Init_SDL(void);
void			OpenWindow_SDL(const char *str, const unsigned int x, const unsigned int y);
unsigned int	LimitFPS_SDL(const unsigned int frame_limit, const unsigned int FPS_LIMIT);
void			ExitWithError_SDL(const char *str);
void			Exit_SDL(void);
void			LoadPic_SDL(const char *path, const unsigned int x, const unsigned int y);
void			start_game(t_player *p1, t_player *p2);
void			init_game(t_player *p1, t_player *p2, t_game_state *game_s);
void			print_game(t_game_state game_s);
void			human_left_click(t_game_state *game_s, t_player *player, SDL_Event event);
void			pred_from_point(t_game_state *game_s, t_player *player, SDL_Point point);
void			add_to_hist(t_game_state *game_s);
void			human_mouse_motion(SDL_Event event, t_game_state *game_s);

SDL_Window		*WINDOW;
SDL_Renderer	*RENDERER;
t_predic		PRED;
t_game_state	HIST[HIST_MAX];
size_t			HIST_NB;
size_t			HIST_LAST;
int				PRINT_PRED;
_Bool			PRINT_HIST;
SDL_Point		LPOS;

#endif