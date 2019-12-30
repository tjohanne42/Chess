#include "chess.h"

static void		init_game_s(t_player *p1, t_player *p2, t_game_state *game_s)
{
	size_t		i;

	i = 0;
	// k = king = roi ; q = queen = reine ; r = rooks = tours ; b = bishops = fous ; n = knights = cavaliers ; p = pawns = pions
	while (i < 64)
	{
		if (i < 16)
			game_s->board[i].color = p1->color;
		else if (i > 47)
			game_s->board[i].color = p2->color;
		if (i == 0 || i == 7 || i == 56 || i == 63)
			game_s->board[i].type = 'r';
		else if (i == 1 || i == 6 || i == 57 || i == 62)
			game_s->board[i].type = 'n';
		else if (i == 2 || i == 5 || i == 58 || i == 61)
			game_s->board[i].type = 'b';
		else if ((i == 3 && p1->color == 'd') || (i == 4 && p1->color == 'w') || (i == 59 && p2->color == 'w') || (i == 60 && p2->color == 'd'))
			game_s->board[i].type = 'q';
		else if ((i == 3 && p1->color == 'w') || (i == 4 && p1->color == 'd') || (i == 59 && p2->color == 'd') || (i == 60 && p2->color == 'w'))
			game_s->board[i].type = 'k';
		else if ((i >  47 && i < 56) || (i > 7 && i < 16))
			game_s->board[i].type = 'p';
		else
			game_s->board[i].type = 0;
		game_s->board[i].pos_x = i % 8 + 1;
		game_s->board[i].pos_y = i / 8 + 1;
		game_s->board[i].rect.x = (game_s->board[i].pos_x - 1) * 60 + 25;
		game_s->board[i].rect.y = (game_s->board[i].pos_y - 1) * 60 + 25;
		game_s->board[i].rect.w = 60;
		game_s->board[i].rect.h = 60;
		i++;
	}
}

void			init_game(t_player *p1, t_player *p2, t_game_state *game_s)
{
	game_s->turn = 'w';
	if (rand() % 2 == 0)
	{
		p1->color = 'w';
		p2->color = 'd';
	}
	else
	{
		p1->color = 'd';
		p2->color = 'w';
	}
	game_s->rock.p1l = SDL_TRUE;
	game_s->rock.p1r = SDL_TRUE;
	game_s->rock.p2l = SDL_TRUE;
	game_s->rock.p2r = SDL_TRUE;
	game_s->checkmate = SDL_FALSE;
	init_game_s(p1, p2, game_s);
	PRED.nb = 0;
	PRED.target.x = 0;
	PRED.target.w = 60;
	PRED.target.h = 60;
	p1->number = 1;
	p2->number = 2;
	HIST_NB = 0;
	HIST_LAST = 0;
	PRINT_HIST = SDL_TRUE;
	PRINT_PRED = -1;
	LPOS.x = 0;
	LPOS.y = 0;
}
