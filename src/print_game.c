#include "Chess.h"

static void		print_predic(void)
{
	size_t		i;

	i = 0;
	if (SDL_SetRenderDrawColor(RENDERER, BROWN, 1) != 0)
		ExitWithError_SDL("SDL_SetRenderDrawColor");
	if (PRED.target.x != 0 && SDL_RenderFillRect(RENDERER, &PRED.target) != 0)
		ExitWithError_SDL("SDL_RenderFillRect");
	while (i < PRED.nb)
	{
		if (SDL_RenderFillRect(RENDERER, &PRED.rect[i]) != 0)
			ExitWithError_SDL("SDL_RenderFillRect");
		i++;
	}
}

static void		print_piece(t_game_state game_s)
{
	size_t		i;
	char		str1[] = "src/pics/pieces/";
	char		str2[] = "wk_60.png";
	char		*tmp;

	i = 0;
	tmp = NULL;
	while (i < 64)
	{
		if (game_s.board[i].type)
		{
			str2[0] = game_s.board[i].color;
			str2[1] = game_s.board[i].type;
			if (!(tmp = ft_strjoin(str1, str2)))
				exit(EXIT_FAILURE);
			LoadPic_SDL(tmp, game_s.board[i].rect.x, game_s.board[i].rect.y);
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
}

static void		print_menu(void)
{
	int			hist_tmp;

	hist_tmp = (HIST_NB - 1) % HIST_MAX;
	if (hist_tmp < 0)
		hist_tmp += HIST_MAX;
	if (HIST_NB > 1 && (unsigned int)hist_tmp != HIST_LAST)
		LoadPic_SDL("src/pics/pieces/wk_60.png", RBACK_X, RBACK_Y);
}

void			print_game(t_game_state game_s)
{
	if (SDL_SetRenderDrawColor(RENDERER, WHITE, 255) != 0)
		ExitWithError_SDL("SDL_SetRenderDrawColor");
	if (SDL_RenderClear(RENDERER) != 0)
		ExitWithError_SDL("SDL_RenderClear");
	LoadPic_SDL("src/pics/chessboard.png", 25, 25);
	print_piece(game_s);
	print_predic();
	print_menu();
}
