/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/11 18:02:03 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display(t_game *game, int i, int j, char sqr_type)
{
	void	*img;

	if (sqr_type == '1')
		img = game->w_img;
	else if (sqr_type == '0')
		img = game->e_img;
	else
		return ;
	mlx_put_image_to_window(game->mlx, game->win, img, (i * ((SQR_SIZE + 1 ) * ZOOM)), (j * ((SQR_SIZE + 1 ) * ZOOM)));
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
	double		j;
	int			size;
	t_player	*player;
	void		*img;

	size = (P_SIZE * ZOOM) / 2;
	player = game->player;
	img = game->p_img;
	mlx_put_image_to_window(game->mlx, game->win, img, (player->posx),
		(player->posy));
	i = 0;
	while (i < 3)
	{
		while( j < size + 1)
		{
			mlx_pixel_put(game->mlx, game->win, player->posx + ((size - 1) + i) + player->posdx
				* j, player->posy + ((size - 1) + i) + player->posdy * j, 0x00FF00FF);
			j += 0.1;
		}
		i++;
	}
}
