/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/03/11 15:49:01 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	dist(float px, float py, float rx, float ry)
{
	return (sqrt(pow(px - rx, 2) + pow(py - ry, 2)));
}

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

void	check_ra(t_rays *ray)
{
	if (ray->ra < 0)
		ray->ra += 2 * PI;
	if (ray->ra > 2 * PI)
		ray->ra -= 2 * PI;
}

// void	draw_2dray(t_game *game, t_rays *ray, float dray)
// {
// 	float	j;

// 	// j = 0;
// 	// (void)dray;
// 	// if (ray->r == 500)
// 	// {
// 	// 	while (j < 8)
// 	// 	{
// 	// 		put_pixel_to_image(game->map_img, ((game->player->posx)
// 	// 				+ (cos(ray->ra) * 5) * j), ((game->player->posy)
// 						+ (sin(ray->ra)
// 	// 					* 5) * j), 0x000000FF);
// 	// 		// mlx_pixel_put(game->mlx, game->win, ((game->player->posx)
// 	// 		// 		+ (cos(ray->ra) * 5) * j), ((game->player->posy)
// 						+ (sin(ray->ra)
// 	// 		// 			* 5) * j), 0x000000FF);
// 	// 		j += 0.5;
// 	// 	}
// 	// }
// 	j = 0;
// 	while (sqrt(pow((game->player->posdx * j), 2) + pow((game->player->posdy
// 					* j), 2)) <= dray && j < 200)
// 	{
// 		mlx_pixel_put(game->mlx, game->win, ((game->player->posx)
// 				+ (cos(ray->ra) * 5) * j), ((game->player->posy) + (sin(ray->ra)
// 					* 5) * j), 0x0000FF00);
// 		j += 1.5;
// 	}
// }

void	calc_draw(t_game *game, t_rays *ray, t_draw *draw)
{
	float	ca;

	draw->ty_off = 0;
	ca = game->player->posa - ray->ra;
	if (ca < 0)
		ca += PI * 2;
	else if (ca > PI * 2)
		ca -= PI * 2;
	ray->dray = ray->dray * cos(ca);
	draw->lineH = (SCR_HEIGHT << 6) / ray->dray;
	draw->ty_step = 64 / draw->lineH;
	if (draw->lineH > SCR_HEIGHT)
	{
		draw->ty_off = (draw->lineH - SCR_HEIGHT) / 2.0;
		draw->lineH = SCR_HEIGHT;
	}
	draw->lineO = (SCR_HEIGHT >> 1) - draw->lineH / 2;
	draw->ty = draw->ty_off * draw->ty_step;
}

int	draw_walls(t_game *game, t_rays *ray, t_draw *draw)
{
	int	color;

	if (ray->dir == 'h')
	{
		if (ray->ra > (180 * RAD_DEG))
			color = get_pixel_color(game->img_no->texture, (int)ray->rx,
					(int)draw->ty);
		else
			color = get_pixel_color_r(game->img_so->texture, (int)ray->rx,
					(int)draw->ty);
		color += 0x020202;
	}
	if (ray->dir == 'v')
	{
		if (ray->ra < (90 * RAD_DEG) || ray->ra > (270 * RAD_DEG))
			color = get_pixel_color(game->img_we->texture, (int)ray->ry,
					(int)draw->ty);
		else
			color = get_pixel_color_r(game->img_ea->texture, (int)ray->ry,
					(int)draw->ty);
	}
	return (color);
}

void	draw_3dray(t_game *game, t_rays *ray)
{
	int		j;
	int		color;
	t_draw	draw;

	calc_draw(game, ray, &draw);
	j = -1;
	while (++j < draw.lineO)
		put_pixel_to_image(game->win_img, ray->r, j,
			game->texinfo->hex_ceiling);
	while (--j > 0)
		put_pixel_to_image(game->win_img, ray->r, SCR_HEIGHT - j,
			game->texinfo->hex_floor);
	j = -1;
	while (++j < draw.lineH)
	{
		color = draw_walls(game, ray, &draw);
		put_pixel_to_image(game->win_img, ray->r, (draw.lineO + j), color);
		draw.ty += draw.ty_step;
	}
}

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

double	ray_hor(t_game *game, t_rays *ray, double dist_h)
{
	double	a_tan;

	ray->dof = 0;
	a_tan = -1 / tan(ray->ra);
	if (ray->ra - PI > EPSILON)
	{
		ray->hry = (((int)game->player->posy >> 6) << 6) - 0.005;
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
		ray->vrx = (((int)game->player->posx >> 6) << 6) - 0.005;
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

void	check_ver_hor(t_rays *ray, double dist_h, double dist_v)
{
	if (floor(dist_h) > floor(dist_v))
		ray->dir = 'v';
	if (floor(dist_v) > floor(dist_h))
		ray->dir = 'h';
	if (dist_h > dist_v)
	{
		ray->rx = ray->vrx;
		ray->ry = ray->vry;
		ray->dray = dist_v;
	}
	else
	{
		ray->rx = ray->hrx;
		ray->ry = ray->hry;
		ray->dray = dist_h;
	}
}

void	draw_ray(t_game *game)
{
	t_rays	ray;
	double	dist_h;
	double	dist_v;

	clear_image(game->win_img);
	ray.r = 0;
	ray.ra = game->player->posa - (RAD_DEG * 30);
	check_ra(&ray);
	while (ray.r < 1000)
	{
		dist_h = ray_hor(game, &ray, dist_h);
		dist_v = ray_ver(game, &ray, dist_v);
		ray.ra += ((60 * RAD_DEG) / 1000);
		check_ra(&ray);
		check_ver_hor(&ray, dist_h, dist_v);
		draw_3dray(game, &ray);
		ray.r++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->win_img->img, 512, 0);
}
