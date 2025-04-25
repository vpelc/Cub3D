/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:24:37 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/25 15:08:21 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*  */
static int	get_pixel_color_mini(t_texture *tex, int x, int y)
{
	int	color;
	int	pixel_index;

	pixel_index = y * tex->size_line + x * (tex->bpp / 8);
	color = *(unsigned int *)(tex->addr + pixel_index);
	return (color);
}

/* decoupe la partie de la map qui sera affichee et affiche */
void	draw_mini_map(t_game *game)
{
	float	img_x;
	float	img_y;
	int		i;
	int		j;

	draw_map(game);
	img_x = game->player->posx - 256;
	img_y = game->player->posy - 256;
	if (game->player->posx > (game->map->width * SQR_SIZE) - 256)
		img_x = (game->map->width * SQR_SIZE) - 512;
	if (game->player->posy > (game->map->height * SQR_SIZE) - 256)
		img_y = (game->map->height * SQR_SIZE) - 512;
	if (game->player->posx < 256 || (game->map->width * SQR_SIZE) < 512)
		img_x = 0;
	if (game->player->posy < 256 || (game->map->height * SQR_SIZE) < 512)
		img_y = 0;
	i = -1;
	while (++i < 512 && i < game->map->height * SQR_SIZE)
	{
		j = -1;
		while (++j < 512 && j < game->map->width * SQR_SIZE)
			put_pixel_to_image(game->minimap_img, j, i,
				get_pixel_color_mini(game->map_img, img_x + j, img_y + i));
	}
	mlx_put_image_to_window(game->mlx, game->win, game->minimap_img->img, 0, 0);
}

/* cree l'image qui prendra la partie qui sera affiche de la map */
void	create_mini_map_img(t_game *game)
{
	t_texture	*tex;

	tex = ft_malloc(game, sizeof(t_texture), 1);
	tex->width = 512;
	tex->height = 512;
	tex->bpp = 32;
	tex->size_line = 2400;
	tex->endian = 0;
	tex->img = mlx_new_image(game->mlx, tex->width, tex->height);
	if (!tex->img)
		return ;
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
	game->minimap_img = tex;
}
