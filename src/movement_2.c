/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:28:42 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/22 14:29:43 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_game *game)
{
	game->player->posa -= 0.1;
	if (game->player->posa < 0)
		game->player->posa += 2 * PI;
	game->player->posdx = cos(game->player->posa) * 5;
	game->player->posdy = sin(game->player->posa) * 5;
	game->player->posdxp = cos(game->player->posa + (90 * RAD_DEG)) * 5;
	game->player->posdyp = sin(game->player->posa + (90 * RAD_DEG)) * 5;
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
	game->player->posdyp = sin(game->player->posa + (90 * RAD_DEG)) * 5;
}
