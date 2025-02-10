/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/07 16:59:31 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../mlx_linux/mlx.h"

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	int		left_key;
	int		right_key;
	int		up_key;
	int		down_key;
	struct s_player	*player;
}	t_game;

typedef struct s_player
{
	int posx;
	int posy;
	t_game *game;
}	t_player;

typedef struct	s_map
{
	char	*name;
	t_game	*game;
}	t_map;

int	close_window(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	// free_img(map->game);
	// free_map(map);
	
	return 1;
}

void	draw_player(t_game *game, t_player *player)
{
	int i;
	int j;
	
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(game->mlx, game->win, player->posx + i, player->posy + j, 0x00FF00FF);
			j++;
		}
		i++;
	}
}

// int	deal_key(int key, t_player *player)
// {
// 	// if (key == 65307)
// 		// close_window(map);
// 	// printf("%i\n", key);
// 	if (key == 119 || key == 65362)
// 		player->posy-= 5;
// 	if (key == 115 || key == 65364)
// 		player->posy+= 5;
// 	if (key == 97 || key == 65361)
// 		player->posx-= 5;
// 	if (key == 100 || key == 65363)
// 		player->posx+= 5;
// 	mlx_clear_window(player->game->mlx, player->game->win);
// 	draw_player(player->game, player);
// 	return (0);
// 	// return (key);
// }

int	key_press(int key, t_game *game)
{
	if (key == 119 || key == 65362)
		game->up_key = 1;
	if (key == 115 || key == 65364)
		game->down_key = 1; 
	if (key == 97 || key == 65361)
		game->left_key = 1;
	if (key == 100 || key == 65363)
		game->right_key = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 119 || key == 65362)
		game->up_key = 0;
	if (key == 115 || key == 65364)
		game->down_key = 0; 
	if (key == 97 || key == 65361)
		game->left_key = 0;
	if (key == 100 || key == 65363)
		game->right_key = 0;
	return (0);
}

int	key_loop(t_game *game)
{
	if (game->up_key)
		game->player->posy-= 5;
	if (game->down_key)
		game->player->posy+= 5;
	if (game->left_key)
		game->player->posx-= 5;
	if (game->right_key)
		game->player->posx+= 5;
	mlx_clear_window(game->mlx, game->win);
	draw_player(game, game->player);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	t_player player;
	// t_map	map;

	(void)argc;
	(void)argv;
	player.posx = 300;
	player.posy = 300;
	player.game = &game;
	game.player = &player;
	game.down_key = 0;
	game.left_key = 0;
	game.up_key = 0;
	game.right_key = 0;
	// check_args(argc, argv);
	// map.name = argv[1];
	// map.game = &game;
	// fill_map(&map);
	// check_map(&map);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1024, 512, "Cub3D");
	draw_player(&game, &player);
	// assign_img(&game);
	// display_map(&map, &game);
	// mlx_key_hook(game.win, deal_key, &player);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, key_loop, &game);
	mlx_loop(game.mlx);
}