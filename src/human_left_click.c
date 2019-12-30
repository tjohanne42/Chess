#include "chess.h"

static _Bool		point_in_chess_board(SDL_Point point)
{
	SDL_Rect		rect;

	rect.x = 25;
	rect.y = 25;
	rect.w = 8 * 60;
	rect.h = 8 * 60;
	if (SDL_PointInRect(&point, &rect))
		return (SDL_TRUE);
	return (SDL_FALSE);
}

static _Bool		point_in_rollback(SDL_Point point)
{
	SDL_Rect		rect;

	rect.x = RBACK_X;
	rect.y = RBACK_Y;
	rect.w = RBACK_W;
	rect.h = RBACK_H;
	if (SDL_PointInRect(&point, &rect))
		return (SDL_TRUE);
	return (SDL_FALSE);
}

static void			do_a_barrell_roll(t_game_state *game_s)
{
	size_t			i;

	i = 0;
	HIST_NB -= 2;
	while (i < 64)
	{
		game_s->board[i].type = HIST[HIST_NB % HIST_MAX].board[i].type;
		game_s->board[i].color = HIST[HIST_NB % HIST_MAX].board[i].color;
		i++;
	}
	game_s->turn = HIST[HIST_NB % HIST_MAX].turn;
	game_s->rock.p1l = HIST[HIST_NB % HIST_MAX].rock.p1l;
	game_s->rock.p1r = HIST[HIST_NB % HIST_MAX].rock.p1r;
	game_s->rock.p2l = HIST[HIST_NB % HIST_MAX].rock.p2l;
	game_s->rock.p2r = HIST[HIST_NB % HIST_MAX].rock.p2r;
	game_s->checkmate = HIST[HIST_NB % HIST_MAX].checkmate;
	HIST_NB++;
}

void				add_to_hist(t_game_state *game_s)
{
	size_t			i;

	i = 0;
	if (HIST_NB % HIST_MAX == HIST_LAST)
	{
		HIST_LAST++;
		if (HIST_LAST == HIST_MAX)
			HIST_LAST = 0;
	}
	while (i < 64)
	{
		HIST[HIST_NB % HIST_MAX].board[i].type = game_s->board[i].type;
		HIST[HIST_NB % HIST_MAX].board[i].color = game_s->board[i].color;
		i++;
	}
	HIST[HIST_NB % HIST_MAX].turn = game_s->turn;
	HIST[HIST_NB % HIST_MAX].rock.p1l = game_s->rock.p1l;
	HIST[HIST_NB % HIST_MAX].rock.p1r = game_s->rock.p1r;
	HIST[HIST_NB % HIST_MAX].rock.p2l = game_s->rock.p2l;
	HIST[HIST_NB % HIST_MAX].rock.p2r = game_s->rock.p2r;
	HIST[HIST_NB % HIST_MAX].checkmate = game_s->checkmate;
	HIST_NB++;
}

static _Bool		point_in_pred(t_game_state *game_s, SDL_Point point)
{
	size_t			i;
	size_t			z;

	i = 0;
	if (!PRED.target.x)
		return (SDL_FALSE);
	while (i < PRED.nb)
	{
		if (SDL_PointInRect(&point, &PRED.rect[i]))
		{
			z = 0;
			while (z < 64)
			{
				game_s->board[z].type = PRED.game_s[i].board[z].type;
				game_s->board[z].color = PRED.game_s[i].board[z].color;
				z++;
			}
			game_s->turn = PRED.game_s[i].turn;
			game_s->rock.p1l = PRED.game_s[i].rock.p1l;
			game_s->rock.p1r = PRED.game_s[i].rock.p1r;
			game_s->rock.p2l = PRED.game_s[i].rock.p2l;
			game_s->rock.p2r = PRED.game_s[i].rock.p2r;
			game_s->checkmate = PRED.game_s[i].checkmate;
			PRED.nb = 0;
			PRED.target.x = 0;
			if (game_s->turn == 'w')
				game_s->turn = 'd';
			else
				game_s->turn = 'w';
			add_to_hist(game_s);
			checkmate(game_s);
			return (SDL_TRUE);
		}
		i++;
	}
	return (SDL_FALSE);
}

void				human_left_click(t_game_state *game_s, t_player *player, SDL_Event event)
{
	SDL_Event		event2;
	size_t			count;
	SDL_Point		point;
	int				hist_tmp;
			
	event2.type = event.type;
	count = 0;
	point.x = event.button.x;
	point.y = event.button.y;
	while (event2.type != SDL_MOUSEBUTTONUP || event2.button.button != SDL_BUTTON_LEFT)
	{
		SDL_PollEvent(&event2);
		if (count == 0)
		{
			hist_tmp = (HIST_NB - 1) % HIST_MAX;
			if (hist_tmp < 0)
				hist_tmp += HIST_MAX;
			if (point_in_chess_board(point))
			{
				if (!point_in_pred(game_s, point))
					pred_from_point(game_s, player, point);
			}
			else if (HIST_NB > 1 && (unsigned int)hist_tmp != HIST_LAST && point_in_rollback(point))
			{
				do_a_barrell_roll(game_s);
				PRED.nb = 0;
				PRED.target.x = 0;
			}
			else
			{
				PRED.nb = 0;
				PRED.target.x = 0;
			}
			print_game(*game_s);
			human_mouse_motion(event, game_s);
		}
		count++;
		if (count > 1000)
			count = 1;
		SDL_RenderPresent(RENDERER);
	}
}
