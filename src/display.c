/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:32:22 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/20 14:32:47 by vpelc            ###   ########.fr       */
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
	mlx_put_image_to_window(game->mlx, game->win, img, (i * ((SQR_SIZE + 1)
				* ZOOM)), (j * ((SQR_SIZE + 1) * ZOOM)));
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
	t_player	*player;
	void		*img;
	int			size;

	player = game->player;
	img = game->p_img;
	size = (P_SIZE * ZOOM) / 2;
	mlx_put_image_to_window(game->mlx, game->win, img, (player->posx - size),
		(player->posy - size));
}