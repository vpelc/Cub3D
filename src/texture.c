/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:37:32 by vpelc             #+#    #+#             */
/*   Updated: 2025/03/03 19:20:29 by vpelc            ###   ########.fr       */
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

void	load_texture(t_game *game)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture) * 1);
	tex->width = 64;
	tex->height = 64;
	tex->bpp = 32;
	tex->size_line = 32;
	tex->endian = 0;
	tex->img = mlx_xpm_file_to_image(game->mlx, "images/test_wall2.xpm", &tex->width, &tex->height);
	if (!tex->img)
		return ;
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
	game->img_list = malloc(sizeof(t_image) * 1);
	game->img_list->texture = tex;
	game->img_list->name = ft_strdup("NO");
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
int	get_pixel_color(t_texture *tex, int x, int y)
{
	int	color;
	int	img_x;
	int	img_y;
	int	pixel_index;

	img_x = x % 64;
	img_y = y % 64;
	pixel_index =  img_y * tex->size_line + img_x * (tex->bpp / 8);
	color = *(unsigned int *)(tex->addr + pixel_index);
	
	return (color);
}

int	get_pixel_color_r(t_texture *tex, int x, int y)
{
	int	color;
	int	img_x;
	int	img_y;
	int	pixel_index;

	img_x =  63 - (x % 64);
	img_y = y % 64;
	pixel_index =  img_y * tex->size_line + img_x * (tex->bpp / 8);
	color = *(unsigned int *)(tex->addr + pixel_index);
	
	return (color);
}