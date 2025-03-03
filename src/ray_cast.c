/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/03/03 19:37:19 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	dist(float px, float py, float rx, float ry)
{
	return (sqrt(pow(px - rx, 2) + pow(py - ry, 2)));
}

void	delta_loop_h(t_game *game, t_rays *ray)
{
	while (ray->dof < 8)
	{
		ray->mx = (int)(ray->hrx) >> 6;
		ray->my = (int)(ray->hry) >> 6;
		if ((ray->mx < 8 && ray->my < 8) && (ray->mx >= 0 && ray->my >= 0)
			&& game->map->tab[ray->my][ray->mx] == '1')
			ray->dof = 8;
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
	while (ray->dof < 8)
	{
		ray->mx = (int)(ray->vrx) >> 6;
		ray->my = (int)(ray->vry) >> 6;
		if ((ray->mx < 8 && ray->my < 8) && (ray->mx >= 0 && ray->my >= 0)
			&& game->map->tab[ray->my][ray->mx] == '1')
			ray->dof = 8;
		else
		{
			ray->vrx += ray->xo;
			ray->vry += ray->yo;
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
	float	ty;
	float	ty_step;
	float	ty_off;
	int		color;
	float	ca;
	float	lineH;
	float	lineO;
	
	ty_off = 0;
	ca = game->player->posa - ray->ra;
	if (ca < 0)
		ca += PI * 2;
	else if (ca > 2 * PI)
		ca -= PI * 2;
	dray = dray * cos(ca);
	lineH = (64 * SCR_HEIGHT) / dray;
	ty_step = game->img_list->texture->height / lineH;
	if (lineH > SCR_HEIGHT)
	{
		ty_off = (lineH - SCR_HEIGHT) / 2.0;
		lineH = SCR_HEIGHT;
	}
	lineO = (SCR_HEIGHT / 2) - lineH / 2;
	j = -1;
	while (++j < lineO)
		put_pixel_to_image(game->win_img, ray->r, j, 0x002222AA);
	while (--j > 0)
		put_pixel_to_image(game->win_img, ray->r, SCR_HEIGHT - j, 0x00228822);
	ty = ty_off * ty_step;
	j = -1;
	while (++j < lineH)
	{
		if (dir == 'h')
		{
			if (ray->ra > (180 * RAD_DEG))
				color = get_pixel_color(game->img_list->texture, (int)ray->rx, (int)ty);
			else
				color = get_pixel_color_r(game->img_list->texture, (int)ray->rx, (int)ty);
			color *= 0.7;
		}
		if (dir == 'v')
		{	
			if (ray->ra < (90 * RAD_DEG) || ray->ra > (270 * RAD_DEG))
				color = get_pixel_color(game->img_list->texture, (int)ray->ry, (int)ty);
			else
				color = get_pixel_color_r(game->img_list->texture, (int)ray->ry, (int)ty);
		}
		put_pixel_to_image(game->win_img, ray->r, (lineO + j), color);
		ty += ty_step;
	}
}


float	ray_hor(t_game *game, t_rays *ray, float distH)
{
	float	aTan;

	ray->dof = 0;
	aTan = -1 / tan(ray->ra);
	if (ray->ra - PI > EPSILON)
	{
		ray->hry = (((int)game->player->posy >> 6) << 6) - 0.00002;
		ray->hrx = (game->player->posy - ray->hry) * aTan + game->player->posx;
		ray->yo = -64;
		ray->xo = -(ray->yo) * aTan;
	}
	if (ray->ra - PI < -EPSILON)
	{
		ray->hry = (((int)game->player->posy >> 6) << 6) + 64;
		ray->hrx = (game->player->posy - ray->hry) * aTan + game->player->posx;
		ray->yo = 64;
		ray->xo = -(ray->yo) * aTan;
	}
	if (ray->ra == 0 || (ray->ra - PI < EPSILON && ray->ra - PI > -EPSILON))
	{
		ray->hrx = game->player->posx;
		ray->hry = game->player->posy;
		ray->dof = 8;
	}
	delta_loop_h(game, ray);
	distH = dist(game->player->posx, game->player->posy, ray->hrx, ray->hry);
	return (distH);
}

float	ray_ver(t_game *game, t_rays *ray, float distV)
{
	float	nTan;

	ray->dof = 0;
	nTan = -tan(ray->ra);
	if (ray->ra - (PI / 2) > EPSILON && ray->ra - ((3 * PI) / 2) < -EPSILON)
	{
		ray->vrx  = (((int)game->player->posx >> 6) << 6) - 0.00002;
		ray->vry = (game->player->posx - ray->vrx) * nTan + game->player->posy;
		ray->xo = -64;
		ray->yo = -(ray->xo) * nTan;
	}
	if (ray->ra - (PI / 2) < -EPSILON || ray->ra - ((3 * PI) / 2) > EPSILON)
	{
		ray->vrx = (((int)game->player->posx >> 6) << 6) + 64;
		ray->vry = (game->player->posx - ray->vrx) * nTan + game->player->posy;
		ray->xo = 64;
		ray->yo = -(ray->xo) * nTan;
	}
	if (ray->ra == 0 || (ray->ra - PI < EPSILON && ray->ra - PI > -EPSILON))
	{
		ray->vrx = game->player->posx;
		ray->vry = game->player->posy;
		ray->dof = 8;
	}
	delta_loop_v(game, ray);
	distV = dist(game->player->posx, game->player->posy, ray->vrx, ray->vry);
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
			ray.rx = ray.vrx;
			ray.ry = ray.vry;
			dray = distV;
			dir = 'v';
		} 
		else
		{
			ray.rx = ray.hrx;
			ray.ry = ray.hry;
			dray = distH;
			dir = 'h';
		}
		draw_2dray(game, &ray, dray);
		draw_3dray(game, &ray, dray, dir);
		ray.r ++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->win_img->img, 512, 48);
}
