/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/22 14:46:28 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
