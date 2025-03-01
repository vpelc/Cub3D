/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:34:02 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/27 18:03:54 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int key, t_game *game)
{
	if (key == 119)
		game->keys->up_key = 1;
	if (key == 115)
		game->keys->down_key = 1;
	if (key == 97)
		game->keys->left_key = 1;
	if (key == 100)
		game->keys->right_key = 1;
	if (key == 65361)
		game->keys->rotl_key = 1;
	if (key == 65363)
		game->keys->rotr_key = 1;
	if (key == 65307)
		close_window(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 119)
		game->keys->up_key = 0;
	if (key == 115)
		game->keys->down_key = 0;
	if (key == 97)
		game->keys->left_key = 0;
	if (key == 100)
		game->keys->right_key = 0;
	if (key == 65361)
		game->keys->rotl_key = 0;
	if (key == 65363)
		game->keys->rotr_key = 0;
	return (0);
}

int	key_loop(t_game *game)
{
	static int	frame_count = 0;

	if (++frame_count % 512 == 0)
	{
		if (game->keys->rotl_key)
			rotate_left(game);
		if (game->keys->rotr_key)
			rotate_right(game);
		if (game->keys->up_key)
			move_up(game);
		if (game->keys->down_key)
			move_down(game);
		if (game->keys->left_key)
			move_left(game);
		if (game->keys->right_key)
			move_right(game);
		// mlx_clear_window(game->mlx, game->win);
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
	game.win = mlx_new_window(game.mlx, 1512, 1000, "Cub3D");
	init_game(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, key_loop, &game);
	mlx_loop(game.mlx);
}
