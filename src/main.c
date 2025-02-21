/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:34:02 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/20 17:18:18 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int key, t_game *game)
{
	if (key == 119 || key == 65362)
		game->keys->up_key = 1;
	if (key == 115 || key == 65364)
		game->keys->down_key = 1;
	if (key == 97 || key == 65361)
		game->keys->left_key = 1;
	if (key == 100 || key == 65363)
		game->keys->right_key = 1;
	if (key == 65307)
		close_window(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 119 || key == 65362)
		game->keys->up_key = 0;
	if (key == 115 || key == 65364)
		game->keys->down_key = 0;
	if (key == 97 || key == 65361)
		game->keys->left_key = 0;
	if (key == 100 || key == 65363)
		game->keys->right_key = 0;
	return (0);
}

int	key_loop(t_game *game)
{
	static int	frame_count = 0;
	int			xo;
	int			yo;
	int			ipx;
	int			ipx_add;
	int			ipx_sub;
	int			ipy;
	int			ipy_add;
	int			ipy_sub;

	if (frame_count++ % 1536 == 0)
	{
		if (game->player->posdx < 0)
			xo = -10;
		else
			xo = 10;
		if (game->player->posdy < 0)
			yo = -10;
		else
			yo = 10;
		ipx = game->player->posx / 64.0;
		ipx_add = (game->player->posx + xo) / 64.0;
		ipx_sub = (game->player->posx - xo) / 64.0;
		ipy = game->player->posy / 64.0;
		ipy_add = (game->player->posy + yo) / 64.0;
		ipy_sub = (game->player->posy - yo) / 64.0;
		if (game->keys->left_key)
		{
			game->player->posa -= 0.1;
			if (game->player->posa < 0)
				game->player->posa += 2 * PI;
			game->player->posdx = cos(game->player->posa) * 5;
			game->player->posdy = sin(game->player->posa) * 5;
		}
		if (game->keys->right_key)
		{
			game->player->posa += 0.1;
			if (game->player->posa > 2 * PI)
				game->player->posa -= 2 * PI;
			game->player->posdx = cos(game->player->posa) * 5;
			game->player->posdy = sin(game->player->posa) * 5;
		}
		if (game->keys->up_key)
		{
			if (game->map->tab[ipy][ipx_add] == '0')
				game->player->posx += game->player->posdx;
			if (game->map->tab[ipy_add][ipx] == '0')
				game->player->posy += game->player->posdy;
		}
		if (game->keys->down_key)
		{
			if (game->map->tab[ipy][ipx_sub] == '0')
				game->player->posx -= game->player->posdx;
			if (game->map->tab[ipy_sub][ipx] == '0')
				game->player->posy -= game->player->posdy;
		}
		mlx_clear_window(game->mlx, game->win);
		draw_map(game);
		draw_player(game);
		draw_ray(game);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	(void)argc;
	(void)argv;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1500 * ZOOM, 1000 * ZOOM, "Cub3D");
	init_game(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, key_loop, &game);
	mlx_loop(game.mlx);
}
