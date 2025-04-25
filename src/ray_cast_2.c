/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:31 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/22 14:47:17 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	delta_loop_h(t_game *game, t_rays *ray)
{
	while (ray->dof < game->map->height)
	{
		ray->mx = (int)(ray->hrx) >> 6;
		ray->my = (int)(ray->hry) >> 6;
		if ((ray->mx < game->map->width && ray->my < game->map->height)
			&& (ray->mx >= 0 && ray->my >= 0)
			&& game->map->cv_tab[ray->my][ray->mx] == '1')
			ray->dof = game->map->height;
		else
		{
			ray->hrx += ray->xo;
			ray->hry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	delta_loop_v(t_game *game, t_rays *ray)
{
	while (ray->dof < game->map->width)
	{
		ray->mx = (int)(ray->vrx) >> 6;
		ray->my = (int)(ray->vry) >> 6;
		if ((ray->mx < game->map->width && ray->my < game->map->height)
			&& (ray->mx >= 0 && ray->my >= 0)
			&& game->map->cv_tab[ray->my][ray->mx] == '1')
			ray->dof = game->map->width;
		else
		{
			ray->vrx += ray->xo;
			ray->vry += ray->yo;
			ray->dof += 1;
		}
	}
}

double	ray_hor(t_game *game, t_rays *ray, double dist_h)
{
	double	a_tan;

	ray->dof = 0;
	a_tan = -1 / tan(ray->ra);
	if (ray->ra - PI > EPSILON)
	{
		ray->hry = (((int)game->player->posy >> 6) << 6) - 0.0005;
		ray->hrx = (game->player->posy - ray->hry) * a_tan + game->player->posx;
		ray->yo = -64;
		ray->xo = -(ray->yo) * a_tan;
	}
	if (ray->ra - PI < -EPSILON)
	{
		ray->hry = (((int)game->player->posy >> 6) << 6) + 64;
		ray->hrx = (game->player->posy - ray->hry) * a_tan + game->player->posx;
		ray->yo = 64;
		ray->xo = -(ray->yo) * a_tan;
	}
	if (ray->ra == 0 || (ray->ra - PI < EPSILON && ray->ra - PI > -EPSILON))
		ray_on_line(game, ray, 'h');
	delta_loop_h(game, ray);
	dist_h = dist(game->player->posx, game->player->posy, ray->hrx, ray->hry);
	return (dist_h);
}

double	ray_ver(t_game *game, t_rays *ray, double dist_v)
{
	double	n_tan;

	ray->dof = 0;
	n_tan = -tan(ray->ra);
	if (ray->ra - (PI / 2) > EPSILON && ray->ra - ((3 * PI) / 2) < -EPSILON)
	{
		ray->vrx = (((int)game->player->posx >> 6) << 6) - 0.0005;
		ray->vry = (game->player->posx - ray->vrx) * n_tan + game->player->posy;
		ray->xo = -SQR_SIZE;
		ray->yo = -(ray->xo) * n_tan;
	}
	if (ray->ra - (PI / 2) < -EPSILON || ray->ra - ((3 * PI) / 2) > EPSILON)
	{
		ray->vrx = (((int)game->player->posx >> 6) << 6) + SQR_SIZE;
		ray->vry = (game->player->posx - ray->vrx) * n_tan + game->player->posy;
		ray->xo = SQR_SIZE;
		ray->yo = -(ray->xo) * n_tan;
	}
	if (ray->ra == 0 || (ray->ra - PI < EPSILON && ray->ra - PI > -EPSILON))
		ray_on_line(game, ray, 'v');
	delta_loop_v(game, ray);
	dist_v = dist(game->player->posx, game->player->posy, ray->vrx, ray->vry);
	return (dist_v);
}
