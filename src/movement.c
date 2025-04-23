/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:33:04 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/22 14:29:59 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_offset(t_game *game, int *xo, int *yo, char dir)
{
	if (dir == 'v')
	{
		if (game->player->posdx < 0)
			*xo = -20;
		else
			*xo = 20;
		if (game->player->posdy < 0)
			*yo = -20;
		else
			*yo = 20;
	}
	if (dir == 'h')
	{
		if (game->player->posdxp < 0)
			*xo = -20;
		else
			*xo = 20;
		if (game->player->posdyp < 0)
			*yo = -20;
		else
			*yo = 20;
	}
}

void	move_up(t_game *game)
{
	int		xo;
	int		yo;
	float	speed;

	speed = 2.0;
	if (game->keys->shift_key)
		speed = 0.5;
	check_offset(game, &xo, &yo, 'v');
	if (game->map->cv_tab[(int)game->player->posy / 64][((int)game->player->posx
			+ xo) / 64] == '0')
		game->player->posx += game->player->posdx * speed;
	if (game->map->cv_tab[((int)game->player->posy + yo)
			/ 64][(int)game->player->posx / 64] == '0')
		game->player->posy += game->player->posdy * speed;
}

void	move_down(t_game *game)
{
	int		xo;
	int		yo;
	float	speed;

	speed = 2.0;
	if (game->keys->shift_key)
		speed = 0.5;
	check_offset(game, &xo, &yo, 'v');
	if (game->map->cv_tab[(int)game->player->posy / 64][((int)game->player->posx
			- xo) / 64] == '0')
		game->player->posx -= game->player->posdx * speed;
	if (game->map->cv_tab[((int)game->player->posy - yo)
			/ 64][(int)game->player->posx / 64] == '0')
		game->player->posy -= game->player->posdy * speed;
}

void	move_left(t_game *game)
{
	int		xo;
	int		yo;
	float	speed;

	speed = 2.0;
	if (game->keys->shift_key)
		speed = 0.5;
	check_offset(game, &xo, &yo, 'h');
	if (game->map->cv_tab[(int)game->player->posy / 64][((int)game->player->posx
			- xo) / 64] == '0')
		game->player->posx -= game->player->posdxp * speed;
	if (game->map->cv_tab[((int)game->player->posy - yo)
			/ 64][(int)game->player->posx / 64] == '0')
		game->player->posy -= game->player->posdyp * speed;
}

void	move_right(t_game *game)
{
	int		xo;
	int		yo;
	float	speed;

	speed = 2.0;
	if (game->keys->shift_key)
		speed = 0.5;
	check_offset(game, &xo, &yo, 'h');
	if (game->map->cv_tab[(int)game->player->posy / 64][((int)game->player->posx
			+ xo) / 64] == '0')
		game->player->posx += game->player->posdxp * speed;
	if (game->map->cv_tab[((int)game->player->posy + yo)
			/ 64][(int)game->player->posx / 64] == '0')
		game->player->posy += game->player->posdyp * speed;
}
