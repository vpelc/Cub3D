/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:56 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/06 14:44:58 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_linux/mlx.h"

// int	deal_key(int key, t_map *map)
// {
// 	if (key == 53)
// 		// close_window(map);
// 	if (key == 13 || key == 126)
// 		move_up(map);
// 	if (key == 1 || key == 125)
// 		move_down(map);
// 	if (key == 0 || key == 123)
// 		move_left(map);
// 	if (key == 2 || key == 124)
// 		move_right(map);
// 	return (0);
// }

typedef struct	s_game
{
	void	*mlx;
	void	*win;
}	t_game;

typedef struct s_player
{
	int posx;
	int posy;
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
			mlx_pixel_put(game->mlx, game->win, player->posx + i, player->posy + j, 0x00112233);
			j++;
		}
		i++;
	}
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
	// mlx_key_hook(game.win, deal_key, &map);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}