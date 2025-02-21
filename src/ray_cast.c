/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/20 17:24:25 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	dist(float px, float py, float rx, float ry)
{
	return (sqrt(pow(px - rx, 2) + pow(py - ry, 2)));
}

void	delta_loop(t_game *game, t_rays *ray)
{
	while (ray->dof < 8)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		if ((ray->mx < 8 && ray->my < 8) && (ray->mx >= 0 && ray->my >= 0)
			&& game->map->tab[ray->my][ray->mx] == '1')
			ray->dof = 8;
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	check_ra(t_rays *ray)
{
	if (ray->ra < 0)
		ray->ra += 2 * PI;
	if (ray->ra > 2 * PI)
		ray->ra -= 2 * PI;
}

void	draw_2dray(t_game *game, t_rays *ray, float dray)
{
	float	j;
	
	j = 0;
	while (sqrt(pow((game->player->posdx * j), 2) + pow((game->player->posdy
					* j), 2)) <= dray && j < 10000000)
	{
		mlx_pixel_put(game->mlx, game->win, ((game->player->posx)
				+ (cos(ray->ra) * 5) * j), ((game->player->posy)
				+ (sin(ray->ra) * 5) * j), 0x00FF0000);
		j += 1.3;
	}
}

void	draw_3dray(t_game *game, t_rays *ray, float dray)
{
	float	j;
	float	ca;
	float	lineH;
	float	lineO;
	
	ca = game->player->posa - ray->ra;
	if (ca < 0)
		ca += PI * 2;
	else if (ca > 2 * PI)
		ca -= PI * 2;
	dray = dray * cos(ca);
	lineH = (64 * 896) / dray;
	if (lineH > 896)
		lineH = 896;
	lineO = 448 - lineH / 2;
	j = 0;
	while (j < lineH)
	{
		mlx_pixel_put(game->mlx, game->win, ray->r * 5 + 545, lineO + j + 30,
			0x00FF0000);
		j += 0.7;
	}
}


float	ray_hor(t_game *game, t_rays *ray, float distH)
{
	float	aTan;

	ray->dof = 0;
	aTan = -1 / tan(ray->ra);
	if (ray->ra - PI > EPSILON)
	{
		ray->ry = (((int)game->player->posy >> 6) << 6) - 0.00002;
		ray->rx = (game->player->posy - ray->ry) * aTan + game->player->posx;
		ray->yo = -64;
		ray->xo = -(ray->yo) * aTan;
	}
	if (ray->ra - PI < -EPSILON)
	{
		ray->ry = (((int)game->player->posy >> 6) << 6) + 64;
		ray->rx = (game->player->posy - ray->ry) * aTan + game->player->posx;
		ray->yo = 64;
		ray->xo = -(ray->yo) * aTan;
	}
	if (ray->ra == 0 || (ray->ra - PI < EPSILON && ray->ra - PI > -EPSILON))
	{
		ray->rx = game->player->posx;
		ray->ry = game->player->posy;
		ray->dof = 8;
	}
	delta_loop(game, ray);
	distH = dist(game->player->posx, game->player->posy, ray->rx, ray->ry);
	return (distH);
}

float	ray_ver(t_game *game, t_rays *ray, float distV)
{
	float	nTan;

	ray->dof = 0;
	nTan = -tan(ray->ra);
	if (ray->ra - (PI / 2) > EPSILON && ray->ra - ((3 * PI) / 2) < -EPSILON)
	{
		ray->rx = (((int)game->player->posx >> 6) << 6) - 0.00002;
		ray->ry = (game->player->posx - ray->rx) * nTan + game->player->posy;
		ray->xo = -64;
		ray->yo = -(ray->xo) * nTan;
	}
	if (ray->ra - (PI / 2) < -EPSILON || ray->ra - ((3 * PI) / 2) > EPSILON)
	{
		ray->rx = (((int)game->player->posx >> 6) << 6) + 64;
		ray->ry = (game->player->posx - ray->rx) * nTan + game->player->posy;
		ray->xo = 64;
		ray->yo = -(ray->xo) * nTan;
	}
	if (ray->ra == 0 || (ray->ra - PI < EPSILON && ray->ra - PI > -EPSILON))
	{
		ray->rx = game->player->posx;
		ray->ry = game->player->posy;
		ray->dof = 8;
	}
	delta_loop(game, ray);
	distV = dist(game->player->posx, game->player->posy, ray->rx, ray->ry);
	return (distV);
}

void	draw_ray(t_game *game)
{
	t_rays	ray;
	float	distH;
	float	distV;
	float	dray;
	

	ray.r = -1;
	ray.ra = game->player->posa - (RAD_DEG * 30);
	check_ra(&ray);
	while (++ray.r < 180)
	{
		distH = ray_hor(game, &ray, distH);
		distV = ray_ver(game, &ray, distV);
		ray.ra += (RAD_DEG / 3);
		check_ra(&ray);
		if (distH > distV)
			dray = distV;
		else
			dray = distH;
		draw_2dray(game, &ray, dray);
		draw_3dray(game, &ray, dray);
	}
}

// void	draw_rays(t_game *game)
// {
// 	t_rays	ray;
// 	float	j;
// 	float	dray;
// 	float	aTan;
// 	float	nTan;
// 	float	distH;
// 	float	distV;
// 	float	lineH;
// 	float	lineO;
// 	float	ca;

// 	ray.r = -1;
// 	ray.ra = game->player->posa - (RAD_DEG * 30);
// 	if (ray.ra < 0)
// 		ray.ra += 2 * PI;
// 	if (ray.ra > 2 * PI)
// 		ray.ra -= 2 * PI;
// 	while (++ray.r < 90)
// 	{
// 		ray.dof = 0;
// 		aTan = -1 / tan(ray.ra);
// 		if (ray.ra - PI > EPSILON)
// 		{
// 			ray.ry = (((int)game->player->posy >> 6) << 6) - 0.00002;
// 			ray.rx = (game->player->posy - ray.ry) * aTan + game->player->posx;
// 			ray.yo = -64;
// 			ray.xo = -(ray.yo) * aTan;
// 		}
// 		if (ray.ra - PI < -EPSILON)
// 		{
// 			ray.ry = (((int)game->player->posy >> 6) << 6) + 64;
// 			ray.rx = (game->player->posy - ray.ry) * aTan + game->player->posx;
// 			ray.yo = 64;
// 			ray.xo = -(ray.yo) * aTan;
// 		}
// 		if (ray.ra == 0 || (ray.ra - PI < EPSILON && ray.ra - PI > -EPSILON))
// 		{
// 			ray.rx = game->player->posx;
// 			ray.ry = game->player->posy;
// 			ray.dof = 8;
// 		}
// 		while (ray.dof < 8)
// 		{
// 			ray.mx = (int)(ray.rx) >> 6;
// 			ray.my = (int)(ray.ry) >> 6;
// 			if ((ray.mx < 8 && ray.my < 8) && (ray.mx >= 0 && ray.my >= 0)
// 				&& game->map->tab[ray.my][ray.mx] == '1')
// 				ray.dof = 8;
// 			else
// 			{
// 				ray.rx += ray.xo;
// 				ray.ry += ray.yo;
// 				ray.dof += 1;
// 			}
// 		}
// 		distH = dist(game->player->posx, game->player->posy, ray.rx, ray.ry);
// 		ray.dof = 0;
// 		nTan = -tan(ray.ra);
// 		if (ray.ra - (PI / 2) > EPSILON && ray.ra - ((3 * PI) / 2) < -EPSILON)
// 		{
// 			ray.rx = (((int)game->player->posx >> 6) << 6) - 0.00002;
// 			ray.ry = (game->player->posx - ray.rx) * nTan + game->player->posy;
// 			ray.xo = -64;
// 			ray.yo = -(ray.xo) * nTan;
// 		}
// 		if (ray.ra - (PI / 2) < -EPSILON || ray.ra - ((3 * PI) / 2) > EPSILON)
// 		{
// 			ray.rx = (((int)game->player->posx >> 6) << 6) + 64;
// 			ray.ry = (game->player->posx - ray.rx) * nTan + game->player->posy;
// 			ray.xo = 64;
// 			ray.yo = -(ray.xo) * nTan;
// 		}
// 		if (ray.ra == 0 || (ray.ra - PI < EPSILON && ray.ra - PI > -EPSILON))
// 		{
// 			ray.rx = game->player->posx;
// 			ray.ry = game->player->posy;
// 			ray.dof = 8;
// 		}
// 		while (ray.dof < 8)
// 		{
// 			ray.mx = (int)(ray.rx) >> 6;
// 			ray.my = (int)(ray.ry) >> 6;
// 			if ((ray.mx < 8 && ray.my < 8) && (ray.mx >= 0 && ray.my >= 0)
// 				&& game->map->tab[ray.my][ray.mx] == '1')
// 				ray.dof = 8;
// 			else
// 			{
// 				ray.rx += ray.xo;
// 				ray.ry += ray.yo;
// 				ray.dof += 1;
// 			}
// 		}
// 		distV = dist(game->player->posx, game->player->posy, ray.rx, ray.ry);
// 		ray.ra += (RAD_DEG / 3) * 2;
// 		if (ray.ra < 0)
// 			ray.ra += 2 * PI;
// 		if (ray.ra > 2 * PI)
// 			ray.ra -= 2 * PI;
// 		if (distH > distV)
// 			dray = distV;
// 		else
// 			dray = distH;
// 		j = 0;
// 		while (sqrt(pow((game->player->posdx * j), 2) + pow((game->player->posdy
// 						* j), 2)) <= dray && j < 10000000)
// 		{
// 			mlx_pixel_put(game->mlx, game->win, ((game->player->posx)
// 					+ (cos(ray.ra) * 5) * j), ((game->player->posy)
// 					+ (sin(ray.ra) * 5) * j), 0x00FF0000);
// 			j += 0.8;
// 		}
// 		ca = game->player->posa - ray.ra;
// 		if (ca < 0)
// 			ca += PI * 2;
// 		else if (ca > 2 * PI)
// 			ca -= PI * 2;
// 		dray = dray * cos(ca);
// 		lineH = (64 * 448) / dray;
// 		if (lineH > 448)
// 			lineH = 448;
// 		lineO = 224 - lineH / 2;
// 		j = 0;
// 		while (j < lineH)
// 		{
// 			mlx_pixel_put(game->mlx, game->win, ray.r * 5 + 530, lineO + j,
// 				0x00FF0000);
// 			j += 0.5;
// 		}
// 	}
// }
