/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:24:37 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/22 14:48:04 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*  */
int	get_pixel_color_mini(t_texture *tex, int x, int y)
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

/* fonction qui remplace mlx_put_pixel place 
	la couleur sur le pixel de l'image*/

void	put_pixel_to_image(t_texture *tex, float x, float y, int color)
{
	int		pixel_x;
	int		pixel_y;
	char	*pixel;

	pixel_x = (int)(x + 0.5);
	pixel_y = (int)(y + 0.5);
	if (pixel_x >= 0 && pixel_x < tex->width && pixel_y >= 0
		&& pixel_y < tex->height)
	{
		pixel = tex->addr + (pixel_y * tex->size_line) + (pixel_x * (tex->bpp
					/ 8));
		*(int *)pixel = color;
	}
}
