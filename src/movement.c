/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:33:04 by vpelc             #+#    #+#             */
/*   Updated: 2025/03/11 14:26:23 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_offset (t_game *game, int *xo, int *yo, char dir)
{
	if (dir == 'v')
	{	
		if (game->player->posdx < 0)
			*xo = -10;
		else
			*xo = 10;
		if (game->player->posdy < 0)
			*yo = -10;
		else
			*yo = 10;
	}
	if (dir == 'h')
	{	
		if (game->player->posdxp < 0)
			*xo = -10;
		else
			*xo = 10;
		if (game->player->posdyp < 0)
			*yo = -10;
		else
			*yo = 10;
	}
}

void	move_up(t_game *game)
{
	int xo;
	int yo;

	check_offset(game, &xo, &yo, 'v');
	if (game->map->cv_tab[(int)game->player->posy / 64][((int)game->player->posx + xo) / 64] == '0')
		game->player->posx += game->player->posdx * 2;
	if (game->map->cv_tab[((int)game->player->posy + yo) / 64][(int)game->player->posx / 64] == '0')
		game->player->posy += game->player->posdy * 2;
}
void	move_down(t_game *game)
{
	int xo;
	int yo;

	check_offset(game, &xo, &yo, 'v');
	if (game->map->cv_tab[(int)game->player->posy / 64][((int)game->player->posx - xo) / 64] == '0')
		game->player->posx -= game->player->posdx * 2;
	if (game->map->cv_tab[((int)game->player->posy - yo) / 64][(int)game->player->posx / 64] == '0')
		game->player->posy -= game->player->posdy * 2;
}

void	move_left(t_game *game)
{
	int xo;
	int yo;

	check_offset(game, &xo, &yo, 'h');
	if (game->map->cv_tab[(int)game->player->posy / 64][((int)game->player->posx - xo) / 64] == '0')
		game->player->posx -= game->player->posdxp * 2;
	if (game->map->cv_tab[((int)game->player->posy - yo) / 64][(int)game->player->posx / 64] == '0')
		game->player->posy -= game->player->posdyp * 2;
}

void	move_right(t_game *game)
{
	int xo;
	int yo;

	check_offset(game, &xo, &yo, 'h');
	if (game->map->cv_tab[(int)game->player->posy / 64][((int)game->player->posx + xo) / 64] == '0')
		game->player->posx += game->player->posdxp * 2;
	if (game->map->cv_tab[((int)game->player->posy + yo) / 64][(int)game->player->posx / 64] == '0')
		game->player->posy += game->player->posdyp * 2;
}

void	rotate_left(t_game *game)
{
	game->player->posa -= 0.1;
	if (game->player->posa < 0)
		game->player->posa += 2 * PI;
	game->player->posdx = cos(game->player->posa) * 5;
	game->player->posdy = sin(game->player->posa) * 5;
	game->player->posdxp = cos(game->player->posa + (90 * RAD_DEG)) * 5;
	game->player->posdyp = sin(game->player->posa + (90 * RAD_DEG)) * 5;;
}

void	rotate_right(t_game *game)
{
	game->player->posa += 0.1;
	if (game->player->posa > 2 * PI)
		game->player->posa -= 2 * PI;
	game->player->posdx = cos(game->player->posa) * 5;
	game->player->posdy = sin(game->player->posa) * 5;
	game->player->posdxp = cos(game->player->posa + (90 * RAD_DEG)) * 5;
	game->player->posdyp = sin(game->player->posa + (90 * RAD_DEG)) * 5;
}

void	mouse_rotate(t_game *game, int move)
{
	move *= 0.2;
	game->player->posa += (move * (0.06 * RAD_DEG));
	if (game->player->posa < 0)
		game->player->posa += 2 * PI;
	game->player->posdx = cos(game->player->posa) * 5;
	game->player->posdy = sin(game->player->posa) * 5;
	game->player->posdxp = cos(game->player->posa + (90 * RAD_DEG)) * 5;
	game->player->posdyp = sin(game->player->posa + (90 * RAD_DEG)) * 5;;
}
