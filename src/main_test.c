/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/14 19:08:51 by vpelc            ###   ########.fr       */
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
	draw_rays(game);
}

void	draw_rays(t_game *game)
{
	t_rays	ray;
	double	drayx;
	float	aTan;
	double	j;

	ray.r = -1;
	ray.ra = game->player->posa;
	// ray.ra = PI / 2;
	while (++ray.r < 1)
	{
		ray.dof = 0;
		aTan = -1 / tan(ray.ra);
		if (ray.ra - PI > EPSILON)
		{
			ray.ry = (((int)game->player->posy >> 6) << 6) - 0.00001;
			ray.rx = (game->player->posy - ray.ry) * aTan + game->player->posx;
			ray.yo = -64;
			ray.xo = -(ray.yo) * aTan;
		}
		if (ray.ra - PI < -EPSILON)
		{
			ray.ry = (((int)game->player->posy >> 6) << 6) + 64;
			ray.rx = (game->player->posy - ray.ry) * aTan + game->player->posx;
			ray.yo = 64;
			ray.xo = -(ray.yo) * aTan;
		}
		if (ray.ra == 0 || (ray.ra - PI < EPSILON && ray.ra - PI > -EPSILON))
		{
			ray.rx = game->player->posx;
			ray.ry = game->player->posy;
			ray.dof = 8;
		}
		while (ray.dof < 8)
		{
			ray.mx = (int)(ray.rx) >> 6;
			ray.my = (int)(ray.ry) >> 6;
			// if ((ray.mx < 8 && ray.my < 8) && (ray.mx > 0 && ray.my > 0))
			// 	printf("my %i | mx %i | char %c\n", ray.my, ray.mx,
			// game->map->tab[ray.my][ray.mx]);
			if ((ray.mx < 8 && ray.my < 8) && (ray.mx >= 0 && ray.my >= 0)
				&& game->map->tab[ray.my][ray.mx] == '1')
				ray.dof = 8;
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
			}
		}
	}
	j = 0;
	drayx = ray.rx - game->player->posx;
	drayx = sqrt(pow(drayx, 2));
	while (sqrt(pow((game->player->posdx * j), 2)) <= drayx && j < 3000)
	{
		mlx_pixel_put(game->mlx, game->win, ((game->player->posx)
				+ game->player->posdx * j), ((game->player->posy)
				+ game->player->posdy * j), 0x00FF00FF);
		j += 0.1;
	}
}
