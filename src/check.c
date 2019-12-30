#include "chess.h"

static _Bool	check_ligne(t_game_state *game_s, char color, size_t k_x, size_t k_y)
{
	size_t		pos;
	size_t		i;

	i = 1;
	while (k_y + i <= 8)
	{
		pos = get_board_from_pos(k_x, k_y + i);
		if (game_s->board[pos].type != 0)
		{
			if ((game_s->board[pos].type == 'r' || game_s->board[pos].type == 'q' || (game_s->board[pos].type == 'k' && i == 1)) && game_s->board[pos].color != color)
				return (SDL_TRUE);
			else
				i = 8;
		}
		i++;
	}
	i = 1;
	while (k_y >= 1 + i)
	{
		pos = get_board_from_pos(k_x, k_y - i);
		if (game_s->board[pos].type != 0)
		{
			if ((game_s->board[pos].type == 'r' || game_s->board[pos].type == 'q' || (game_s->board[pos].type == 'k' && i == 1)) && game_s->board[pos].color != color)
				return (SDL_TRUE);
			else
				i = 8;
		}
		i++;
	}
	i = 1;
	while (k_x + i <= 8)
	{
		pos = get_board_from_pos(k_x + i, k_y);
		if (game_s->board[pos].type != 0)
		{
			if ((game_s->board[pos].type == 'r' || game_s->board[pos].type == 'q' || (game_s->board[pos].type == 'k' && i == 1)) && game_s->board[pos].color != color)
				return (SDL_TRUE);
			else
				i = 8;
		}
		i++;
	}
	i = 1;
	while (k_x >= 1 + i)
	{
		pos = get_board_from_pos(k_x - i, k_y);
		if (game_s->board[pos].type != 0)
		{
			if ((game_s->board[pos].type == 'r' || game_s->board[pos].type == 'q' || (game_s->board[pos].type == 'k' && i == 1)) && game_s->board[pos].color != color)
				return (SDL_TRUE);
			else
				i = 8;
		}
		i++;
	}
	return (SDL_FALSE);
}

static _Bool	check_diag(t_game_state *game_s, char color, size_t k_x, size_t k_y, t_player *player)
{
	size_t		pos;
	size_t		i;

	i = 1;
	while (k_x >= i + 1 && k_y >= i + 1)
	{
		pos = get_board_from_pos(k_x - i, k_y - i);
		if (game_s->board[pos].type != 0)
		{
			if ((game_s->board[pos].type == 'b' || game_s->board[pos].type == 'q' || (game_s->board[pos].type == 'k' && i == 1) ||
				(game_s->board[pos].type == 'p' && i == 1 && player->number == 2)) && game_s->board[pos].color != color)
				return (SDL_TRUE);
			else
				i = 8;
		}
		i++;
	}
	i = 1;
	while (k_x >= 1 + i && k_y + i <= 8)
	{
		pos = get_board_from_pos(k_x - i, k_y + i);
		if (game_s->board[pos].type != 0)
		{
			if ((game_s->board[pos].type == 'b' || game_s->board[pos].type == 'q' || (game_s->board[pos].type == 'k' && i == 1) ||
				(game_s->board[pos].type == 'p' && i == 1 && player->number == 1)) && game_s->board[pos].color != color)
				return (SDL_TRUE);
			else
				i = 8;
		}
		i++;
	}
	i = 1;
	while (k_x + i <= 8 && k_y + i <= 8)
	{
		pos = get_board_from_pos(k_x + i, k_y + i);
		if (game_s->board[pos].type != 0)
		{
			if ((game_s->board[pos].type == 'b' || game_s->board[pos].type == 'q' || (game_s->board[pos].type == 'k' && i == 1) ||
				(game_s->board[pos].type == 'p' && i == 1 && player->number == 1)) && game_s->board[pos].color != color)
				return (SDL_TRUE);
			else
				i = 8;
		}
		i++;
	}
	i = 1;
	while (k_x + i <= 8 && k_y >= 1 + i)
	{
		pos = get_board_from_pos(k_x + i, k_y - i);
		if (game_s->board[pos].type != 0)
		{
			if ((game_s->board[pos].type == 'b' || game_s->board[pos].type == 'q' || (game_s->board[pos].type == 'k' && i == 1) ||
				(game_s->board[pos].type == 'p' && i == 1 && player->number == 2)) && game_s->board[pos].color != color)
				return (SDL_TRUE);
			else
				i = 8;
		}
		i++;
	}
	return (SDL_FALSE);
}

static _Bool	check_knight(t_game_state *game_s, char color, size_t k_x, size_t k_y)
{
	size_t		pos;

	if (k_x >= 2 && k_y >= 3)
	{
		pos = get_board_from_pos(k_x - 1, k_y - 2);
		if (game_s->board[pos].type == 'n' && game_s->board[pos].color != color)
			return (SDL_TRUE);
	}
	if (k_x <= 7 && k_y >= 3)
	{
		pos = get_board_from_pos(k_x + 1, k_y - 2);
		if (game_s->board[pos].type == 'n' && game_s->board[pos].color != color)
			return (SDL_TRUE);
	}
	if (k_x <= 6 && k_y >= 2)
	{
		pos = get_board_from_pos(k_x + 2, k_y - 1);
		if (game_s->board[pos].type == 'n' && game_s->board[pos].color != color)
			return (SDL_TRUE);
	}
	if (k_x <= 6 && k_y <= 7)
	{
		pos = get_board_from_pos(k_x + 2, k_y + 1);
		if (game_s->board[pos].type == 'n' && game_s->board[pos].color != color)
			return (SDL_TRUE);
	}
	if (k_x <= 7 && k_y <= 6)
	{
		pos = get_board_from_pos(k_x + 1, k_y + 2);
		if (game_s->board[pos].type == 'n' && game_s->board[pos].color != color)
			return (SDL_TRUE);
	}
	if (k_x >= 2 && k_y <= 6)
	{
		pos = get_board_from_pos(k_x - 1, k_y + 2);
		if (game_s->board[pos].type == 'n' && game_s->board[pos].color != color)
			return (SDL_TRUE);
	}
	if (k_x >= 3 && k_y <= 7)
	{
		pos = get_board_from_pos(k_x - 2, k_y + 1);
		if (game_s->board[pos].type == 'n' && game_s->board[pos].color != color)
			return (SDL_TRUE);
	}
	if (k_x >= 3 && k_y >= 2)
	{
		pos = get_board_from_pos(k_x - 2, k_y - 1);
		if (game_s->board[pos].type == 'n' && game_s->board[pos].color != color)
			return (SDL_TRUE);
	}
	return (SDL_FALSE);
}

_Bool		check(t_game_state *game_s, char color, t_player *player)
{
	size_t		k;
	size_t		k_x;
	size_t		k_y;
	
	k = 0;
	while ((game_s->board[k].color != color || game_s->board[k].type != 'k') && k < 64)
		k++;
	if (k == 64)
		return (SDL_FALSE);
	k_x = game_s->board[k].pos_x;
	k_y = game_s->board[k].pos_y;
	if (check_ligne(game_s, color, k_x, k_y))
		return (SDL_TRUE);
	if (check_diag(game_s, color, k_x, k_y, player))
		return (SDL_TRUE);
	if (check_knight(game_s, color, k_x, k_y))
		return (SDL_TRUE);
	return (SDL_FALSE);
}