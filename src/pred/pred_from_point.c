#include "chess.h"

static size_t	get_board_from_pix(t_game_state *game_s, size_t x, size_t y)
{
	size_t		i;

	i = 0;
	x = (x - 25) / 60 + 1;
	y = (y - 25) / 60 + 1;
	while (i < 64)
	{
		if (game_s->board[i].pos_x == x && game_s->board[i].pos_y == y)
			return (i);
		i++;
	}
	return (i);
}

static size_t	get_board_from_pos(size_t x, size_t y)
{
	return (x - 1 + (y - 1) * 8);
}

static void		add_pos_to_pred(size_t x, size_t y, t_game_state *game_s)
{
	size_t		n_pos;
	size_t		pos;
	size_t		i;

	// cpy game_s into PRED.game_s[PRED.nb]
	i = 0;
	while (i < 64)
	{
		PRED.game_s[PRED.nb].board[i].type = game_s->board[i].type;
		PRED.game_s[PRED.nb].board[i].color = game_s->board[i].color;
		i++;
	}
	PRED.game_s[PRED.nb].turn = game_s->turn;
	PRED.game_s[PRED.nb].rock.p1l = game_s->rock.p1l;
	PRED.game_s[PRED.nb].rock.p1r = game_s->rock.p1r;
	PRED.game_s[PRED.nb].rock.p2l = game_s->rock.p2l;
	PRED.game_s[PRED.nb].rock.p2r = game_s->rock.p2r;
	pos = get_board_from_pix(game_s, PRED.target.x, PRED.target.y);
	n_pos = get_board_from_pos(x, y);
	PRED.game_s[PRED.nb].board[n_pos].type = PRED.game_s[PRED.nb].board[pos].type;
	PRED.game_s[PRED.nb].board[n_pos].color = PRED.game_s[PRED.nb].board[pos].color;
	PRED.game_s[PRED.nb].board[pos].type = 0;
	PRED.rect[PRED.nb].x = game_s->board[n_pos].rect.x;
	PRED.rect[PRED.nb].y = game_s->board[n_pos].rect.y;
	PRED.rect[PRED.nb].h = 60;
	PRED.rect[PRED.nb].w = 60;
	PRED.nb++;
}

void			pred_from_point(t_game_state *game_s, t_player *player, SDL_Point point)
{
	size_t		pos;

	PRED.nb = 0;
	PRED.target.x = 0;
	pos = get_board_from_pix(game_s, point.x, point.y);
	if (game_s->board[pos].color != player->color || !game_s->board[pos].type)
		return;
	PRED.target.x = game_s->board[pos].rect.x;
	PRED.target.y = game_s->board[pos].rect.y;
	if (game_s->board[pos].type == 'p' && game_s->board[pos].pos_y > 1 && player->number == 2)
		add_pos_to_pred(game_s->board[pos].pos_x, game_s->board[pos].pos_y - 1, game_s);
	else if (game_s->board[pos].type == 'p' && game_s->board[pos].pos_y < 8 && player->number == 1)
		add_pos_to_pred(game_s->board[pos].pos_x, game_s->board[pos].pos_y + 1, game_s);
}
