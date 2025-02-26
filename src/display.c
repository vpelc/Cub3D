/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:32:22 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/26 22:42:15 by vpelc            ###   ########.fr       */
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
	mlx_put_image_to_window(game->mlx, game->win, img, (i * ((SQR_SIZE))), (j
			* ((SQR_SIZE))));
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
	size = (P_SIZE) / 2;
	mlx_put_image_to_window(game->mlx, game->win, img, (player->posx - size),
		(player->posy - size));
}

void	put_pixel_to_image(t_texture *tex, float x, float y, int color)
{
	int		pixel_x;
	int		pixel_y;
	char	*pixel;

	pixel_x = (int)(x + 0.5);
	pixel_y = (int)(y + 0.5);
	// Check if within screen bounds to prevent memory errors
	// if (pixel_x >= 0 && pixel_x < 800 && pixel_y >= 0 && pixel_y < 600)
	// {
	pixel = tex->addr + (pixel_y * tex->size_line) + (pixel_x * (tex->bpp / 8));
	*(int *)pixel = color;
	// }
}

// void	draw_floor(t_game *game)
// {

// }