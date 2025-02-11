/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:34:02 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/11 14:06:13 by vpelc            ###   ########.fr       */
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
	static int frame_count = 0;

	if (frame_count++ % 60 == 0)
	{
		if (game->keys->up_key)
			game->player->posy-= 5;
		if (game->keys->down_key)
			game->player->posy+= 5;
		if (game->keys->left_key)
			game->player->posx-= 5;
		if (game->keys->right_key)
			game->player->posx+= 5;
	}
	mlx_clear_window(game->mlx, game->win);
	draw_player(game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	(void)argc;
	(void)argv;
	init_game(&game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1024, 512, "Cub3D");
	draw_player(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, key_loop, &game);
	mlx_loop(game.mlx);
}
