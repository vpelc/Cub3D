/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/03/01 15:54:49 by vpelc            ###   ########.fr       */
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
					* j), 2)) <= dray && j < 200)
	{
		mlx_pixel_put(game->mlx, game->win, ((game->player->posx)
				+ (cos(ray->ra) * 5) * j), ((game->player->posy)
				+ (sin(ray->ra) * 5) * j), 0x0000FF00);
		j += 1.5;
	}
}

void	draw_3dray(t_game *game, t_rays *ray, float dray, char dir)
{
	int		j;
	int		color;
	float	ca;
	float	lineH;
	float	lineO;
	
	ca = game->player->posa - ray->ra;
	if (ca < 0)
		ca += PI * 2;
	else if (ca > 2 * PI)
		ca -= PI * 2;
	dray = dray * cos(ca);
	lineH = (64 * SCR_HEIGHT) / dray;
	if (lineH > SCR_HEIGHT)
		lineH = SCR_HEIGHT;
	lineO = (SCR_HEIGHT / 2) - lineH / 2;
	j = -1;
	while (++j < lineO)
		put_pixel_to_image(game->win_img, ray->r, j, 0x002222AA);
	while (--j > 0)
		put_pixel_to_image(game->win_img, ray->r, SCR_HEIGHT - j, 0x00228822);
	/*j = -1;
 	while (++j < lineH)
	{
		if (dir == 'v')
			put_pixel_to_image(game->win_img, ray->r, (lineO + j), 0x00FF0000);
		if (dir == 'h')
			put_pixel_to_image(game->win_img, ray->r, (lineO + j), 0x00CC0000);
	} */
	j = -1;
	while (++j < lineH)
	{
		color = get_pixel_color(game, game->img_list->texture, (float)ray->rx, (float)ray->ry + j);
		if (dir == 'v')
			color *= 0.8;
		put_pixel_to_image(game->win_img, ray->r, (lineO + j), color);
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
	char	dir;

	clear_image(game->win_img);
	ray.r = 0;
	ray.ra = game->player->posa - (RAD_DEG * 30);
	check_ra(&ray);
	while (ray.r < 1000)
	{
		distH = ray_hor(game, &ray, distH);
		distV = ray_ver(game, &ray, distV);
		ray.ra += ((60 * RAD_DEG) / 1000);
		check_ra(&ray);
		if (distH > distV)
		{
			dray = distV;
			dir = 'v';
		}
		else
		{
			dray = distH;
			dir = 'h';
		}
		draw_2dray(game, &ray, dray);
		draw_3dray(game, &ray, dray, dir);
		ray.r ++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->win_img->img, 512, 48);
}
