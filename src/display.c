/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:43:17 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/25 15:18:04 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* cree l'image qui prendra la map dans sa totalite  */
void	create_map_img(t_game *game)
{
	t_texture	*tex;

	tex = ft_malloc(game, sizeof(t_texture), 1);
	tex->width = game->map->width << 6;
	tex->height = game->map->height << 6;
	tex->bpp = 32;
	tex->size_line = 2400;
	tex->endian = 0;
	tex->img = mlx_new_image(game->mlx, tex->width, tex->height);
	if (!tex->img)
		return ;
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
	game->map_img = tex;
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

/* dessine le joueur sur la minimap */
static void	draw_player(t_game *game)
{
	int		size;
	int		i;
	int		j;
	float	k;

	size = (P_SIZE) / 2;
	i = -size - 1;
	while (++i < size)
	{
		j = -size - 1;
		while (++j < size)
		{
			put_pixel_to_image(game->map_img, (game->player->posx + j),
				(game->player->posy + i), 0x0000FF);
		}
	}
	k = 0;
	while (k < 6)
	{
		put_pixel_to_image(game->map_img, ((game->player->posx)
				+ (game->player->posdx) * k), ((game->player->posy)
				+ (game->player->posdy) * k), 0x000000FF);
		k += 0.2;
	}
}

/* dessine les differentes cases (murs ou sol) pour la map */
static void	draw_square(t_game *game, int x, int y, char sqr_type)
{
	int			color;
	int			i;
	int			j;

	i = -1;
	color = 0x000000;
	if (sqr_type == '0')
		color = 0xFFFFFF;
	if (sqr_type == '1')
		color = 0x505050;
	while (++i < SQR_SIZE)
	{
		j = -1;
		while (++j < SQR_SIZE)
		{
			if (j == 0 || i == 0)
				put_pixel_to_image(game->map_img, (x * SQR_SIZE) + j, (y
						* SQR_SIZE) + i, 0x000000);
			else
				put_pixel_to_image(game->map_img, (x * SQR_SIZE) + j, (y
						* SQR_SIZE) + i, color);
		}
	}
}

/* dessine la map dans sa totalite (joueur + cases) */
void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	clear_image(game->map_img);
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			draw_square(game, j, i, game->map->cv_tab[i][j]);
			j++;
		}
		i++;
	}
	draw_player(game);
}
