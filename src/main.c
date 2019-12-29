#include "chess.h"

static void		init_pred_hist(void)
{
	size_t		i;
	size_t		z;

	i = 0;
	while (i < 64)
	{
		z = 0;
		while (z < 64)
		{
			PRED.game_s[i].board[z].pos_x = z % 8 + 1;
			PRED.game_s[i].board[z].pos_y = z / 8 + 1;
			PRED.game_s[i].board[z].rect.x = (PRED.game_s[i].board[z].pos_x - 1) * 60 + 25;
			PRED.game_s[i].board[z].rect.y = (PRED.game_s[i].board[z].pos_y - 1) * 60 + 25;
			PRED.game_s[i].board[z].rect.w = 60;
			PRED.game_s[i].board[z].rect.h = 60;
			z++;
		}
		i++;
	}
	i = 0;
	while (i < HIST_MAX)
	{
		z = 0;
		while (z < 64)
		{
			HIST[i].board[z].pos_x = z % 8 + 1;
			HIST[i].board[z].pos_y = z / 8 + 1;
			HIST[i].board[z].rect.x = (HIST[i].board[z].pos_x - 1) * 60 + 25;
			HIST[i].board[z].rect.y = (HIST[i].board[z].pos_y - 1) * 60 + 25;
			HIST[i].board[z].rect.w = 60;
			HIST[i].board[z].rect.h = 60;
			z++;
		}
		i++;
	}
}

int				main(int argc, char **argv)
{
	t_player	p1;
	t_player	p2;

	if (argc > 1)
	{
		ft_printf("Error : %s\n", argv[argc - 1]);
		return (EXIT_FAILURE);
	}
	WINDOW = NULL;
	RENDERER = NULL;
	srand(time(NULL));
	Init_SDL();
	OpenWindow_SDL("Chess", 8 * 60 + 550, 8 * 60 + 50);
	init_pred_hist();
	p1.human = SDL_TRUE;
	p2.human = SDL_TRUE;
	start_game(&p1, &p2);
	Exit_SDL();
	return (EXIT_SUCCESS);
}
