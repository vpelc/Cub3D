/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:43:17 by vpelc             #+#    #+#             */
/*   Updated: 2025/03/05 11:28:59 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* cree l'image qui prendra la map dans sa totalite  */
void	create_map_img(t_game *game)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture) * 1);
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

/* cree l'image qui prendra la partie qui sera affiche de la map */
void	create_mini_map_img(t_game *game)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture) * 1);
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

/* dessine le joueur sur la minimap */
void	draw_player(t_game *game)
{
	t_player	*player;
	int			size;
	int			i;
	int			j;
	float		k;

	player = game->player;
	size = (P_SIZE) / 2;
	i = -size;
	while (i < size)
	{
		j = -size;
		while (j < size)
		{
			put_pixel_to_image(game->map_img, (player->posx + j), (player->posy
					+ i), 0x0000FF);
			j++;
		}
		i++;
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
void	draw_square(t_game *game, int x, int y, char sqr_type)
{
	t_player	*player;
	int			color;
	int			i;
	int			j;

	player = game->player;
	i = 0;
	color = 0x000000;
	if (sqr_type == '0')
		color = 0xFFFFFF;
	if (sqr_type == '1')
		color = 0x505050;
	while (i < SQR_SIZE)
	{
		j = 0;
		while (j < SQR_SIZE)
		{
			if (j == 0 || i == 0)
				put_pixel_to_image(game->map_img, (x * SQR_SIZE) + j, (y
						* SQR_SIZE) + i, 0x000000);
			else
				put_pixel_to_image(game->map_img, (x * SQR_SIZE) + j, (y
						* SQR_SIZE) + i, color);
			j++;
		}
		i++;
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
			draw_square(game, j, i, game->map->tab[i][j]);
			j++;
		}
		i++;
	}
	draw_player(game);
	// mlx_put_image_to_window(game->mlx, game->win, game->map_img->img, 0, 0);
}
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
	if (game->player->posx < 256)
		img_x = 0;
	if (game->player->posy < 256)
		img_y = 0;
	if (game->player->posx > (game->map->width * SQR_SIZE) - 256)
		img_x = (game->map->width * SQR_SIZE) - 512;
	if (game->player->posy > (game->map->height * SQR_SIZE) - 256)
		img_y = (game->map->height * SQR_SIZE) - 512;
	i = -1;
	while (++i < 512)
	{
		j = -1;
		while (++j < 512)
			put_pixel_to_image(game->minimap_img, j, i,
				get_pixel_color_mini(game->map_img, img_x + j, img_y + i));
	}
	mlx_put_image_to_window(game->mlx, game->win, game->minimap_img->img, 0, 0);
}
