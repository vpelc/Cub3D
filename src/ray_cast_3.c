/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:11 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/22 14:47:34 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_on_line(t_game *game, t_rays *ray, char dir)
{
	if (dir == 'v')
	{
		ray->vrx = game->player->posx;
		ray->vry = game->player->posy;
		ray->dof = game->map->height;
	}
	if (dir == 'h')
	{
		ray->hrx = game->player->posx;
		ray->hry = game->player->posy;
		ray->dof = game->map->height;
	}
}

void	check_ver_hor(t_rays *ray, double dist_h, double dist_v)
{
	if (dist_h > dist_v)
	{
		ray->rx = ray->vrx;
		ray->ry = ray->vry;
		ray->dray = dist_v;
		ray->dir = 'v';
	}
	else
	{
		ray->rx = ray->hrx;
		ray->ry = ray->hry;
		ray->dray = dist_h;
		ray->dir = 'h';
	}
}

void	check_ra(t_rays *ray)
{
	if (ray->ra < 0)
		ray->ra += 2 * PI;
	if (ray->ra > 2 * PI)
		ray->ra -= 2 * PI;
}

float	dist(float px, float py, float rx, float ry)
{
	return (sqrt(pow(px - rx, 2) + pow(py - ry, 2)));
}
