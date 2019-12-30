#include "chess.h"

void			checkmate(t_game_state *game_s)
{
	if (game_s->turn == 'w')
		game_s->turn = 'w';
}

void				IA_play(t_game_state *game_s, t_player *player)
{
	//useless
	if (player->human == SDL_TRUE)
		ft_printf("blbl\n");
	//end useless
	if (game_s->turn == 'w')
		game_s->turn = 'd';
	else
		game_s->turn = 'w';
	checkmate(game_s);
	//print_game(game_s);
}

static void		print_red_diff(t_game_state n_s, t_game_state o_s)
{
	size_t		i;

	i = 0;

	if (SDL_SetRenderDrawColor(RENDERER, RED, 1) != 0)
		ExitWithError_SDL("SDL_SetRenderDrawColor");
	while (i < 64)
	{
		if(n_s.board[i].type != o_s.board[i].type || n_s.board[i].color != o_s.board[i].color)
		{
			if (SDL_RenderFillRect(RENDERER, &n_s.board[i].rect) != 0)
				ExitWithError_SDL("SDL_RenderFillRect");
		}
		i++;

	}
}

void			human_mouse_motion(SDL_Event event, t_game_state *game_s)
{
	SDL_Rect		rect;
	size_t			i;
	int				hist_tmp;

	if (event.type == SDL_MOUSEMOTION)
	{
		LPOS.x = event.motion.x;
		LPOS.y = event.motion.y;
	}
	rect.x = RBACK_X;
	rect.y = RBACK_Y;
	rect.w = RBACK_W;
	rect.h = RBACK_H;
	i = 0;
	while (i < PRED.nb)
	{
		if (PRINT_PRED == - 1 && SDL_PointInRect(&LPOS, &PRED.rect[i]))
		{
			print_game(PRED.game_s[i]);
			print_red_diff(PRED.game_s[i], *game_s);
			SDL_RenderPresent(RENDERER);
			SDL_Delay(20);
			PRINT_PRED = i;
			i = PRED.nb;
		}
		i++;
	}
	if (PRINT_PRED != -1 && !SDL_PointInRect(&LPOS, &PRED.rect[PRINT_PRED]))
	{
		print_game(*game_s);
		SDL_RenderPresent(RENDERER);
		PRINT_PRED = -1;
	}
	hist_tmp = (HIST_NB - 1) % HIST_MAX;
	if (hist_tmp < 0)
		hist_tmp += HIST_MAX;
	if (HIST_NB > 1 && (unsigned int)hist_tmp != HIST_LAST && SDL_PointInRect(&LPOS, &rect))
	{
		print_game(HIST[(HIST_NB - 2) % HIST_MAX]);
		print_red_diff(HIST[(HIST_NB - 2) % HIST_MAX], *game_s);
		SDL_RenderPresent(RENDERER);
		SDL_Delay(20);
		PRINT_HIST = SDL_TRUE;

	}
	else if (PRINT_HIST && !SDL_PointInRect(&LPOS, &rect))
	{
		PRINT_HIST = SDL_FALSE;
		print_game(*game_s);
		SDL_RenderPresent(RENDERER);
	}
}

void				start_game(t_player *p1, t_player *p2)
{
	t_game_state	game_s;
	SDL_Event		event;
	_Bool			EXIT_VALUE;

	init_game(p1, p2, &game_s);
	if (p1->human == SDL_TRUE || p2->human == SDL_TRUE)
	{
		print_game(game_s);
		add_to_hist(&game_s);
		HIST_LAST = 0;
	}
	EXIT_VALUE = SDL_FALSE;
	while (!EXIT_VALUE)
	{
		if (game_s.turn == p1->color && p1->human == SDL_FALSE && !game_s.checkmate)
			IA_play(&game_s, p1);
		else if (game_s.turn == p2->color && p2->human == SDL_FALSE && !game_s.checkmate)
			IA_play(&game_s, p2);
		if (p1->human == SDL_TRUE || p2->human == SDL_TRUE)
		{
			event.type = 0;
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT)
				EXIT_VALUE = SDL_TRUE;
			else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT &&
				game_s.turn == p1->color && p1->human == SDL_TRUE && !game_s.checkmate)
				human_left_click(&game_s, p1, event);
			else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT &&
				game_s.turn == p2->color && p2->human == SDL_TRUE && !game_s.checkmate)
				human_left_click(&game_s, p2, event);
			else if (event.type == SDL_MOUSEMOTION && !game_s.checkmate)
				human_mouse_motion(event, &game_s);
			SDL_RenderPresent(RENDERER);
		}
	}
}
