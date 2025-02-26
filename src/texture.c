/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:37:32 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/25 15:21:45 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_win_texture(t_game *game)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture) * 1);
	tex->width = 1000;
	tex->height = 1000;
	tex->bpp = 32;
	tex->size_line = 1028;
	tex->endian = 0;
	tex->img = mlx_new_image(game->mlx, 1000, 1000);
	if (!tex->img)
		return ;
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
	game->win_img = tex;
}

void	clear_image(t_texture *tex)
{
	int x;
	int y;
	int color;

	color = 0x00000000;
	for (y = 0; y < tex->height; y++)
	{
		for (x = 0; x < tex->width; x++)
		{
			put_pixel_to_image(tex, x, y, color);
		}
	}
}