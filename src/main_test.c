/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/11 14:46:55 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display(t_game *game, int i, int j, char sqr_type)
{
	void	*img;

	if (sqr_type == '1')
		img = game->e_img;
	else if (sqr_type == '0')
		img = game->w_img;
	else
		return ;
	mlx_put_image_to_window(game->mlx, game->win, img, (i * 64), (j * 64));
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			display(game, j, i, game->map->tab[i][j]);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	int			i;
	int			j;
	t_player	*player;

	player = game->player;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(game->mlx, game->win, player->posx + i, player->posy
				+ j, 0x00FF00FF);
			j++;
		}
		i++;
	}
}
