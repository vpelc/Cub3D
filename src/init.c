/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:36:09 by vpelc             #+#    #+#             */
/*   Updated: 2025/03/05 12:29:26 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	fake_init_map(t_map *map)
{
	char	**tab;
	int		i;

	i = -1;
	tab = malloc(sizeof(char *) * 12);
	if (!tab)
		return (1);
	while (++i < 8)
		tab[i] = malloc(sizeof(char) * 12);
	tab[i] = NULL;
	tab[0] = "11111111111";
	tab[1] = "1001  10001";
	tab[2] = "10011 10001";
	tab[3] = "10001110011";
	tab[4] = "10000000011";
	tab[5] = "11001000101";
	tab[6] = "11011000001";
	tab[7] = "10000000011";
	tab[8] = "10000110011";
	tab[9] = "10110000011";
	tab[10] = "11111111111";
	map->height = 11;
	map->width = 11;
	map->tab = tab;
	return (0);
}

int	init_game(t_game *game)
{
	t_player	*player;
	t_map		*map;
	t_keys		*keys;
	int			size_p;
	int			size_s;

	size_p = P_SIZE;
	size_s = SQR_SIZE;
	player = ft_malloc(game, sizeof(t_player), 1);
	keys = ft_malloc(game, sizeof(t_keys), 1);
	map = ft_malloc(game, sizeof(t_map), 1);
	
	player->game = game;
	game->player = player;
	map->game = game;
	game->map = map;
	player->posx = 300; // change to proper value
	player->posy = 300; // same
	// player->posa = 2 * PI;
	player->posdx = cos(player->posa) * 5;
	player->posdy = sin(player->posa) * 5;
	game->player->posdxp = cos(game->player->posa + (90 * RAD_DEG)) * 5;
	game->player->posdyp = sin(game->player->posa + (90 * RAD_DEG)) * 5;
	keys->down_key = 0;
	keys->left_key = 0;
	keys->right_key = 0;
	keys->up_key = 0;
	game->keys = keys;
	fake_init_map(map);
	// game->p_img = mlx_xpm_file_to_image(game->mlx, "images/player.xpm", &size_p,
	// 		&size_p);
	// game->w_img = mlx_xpm_file_to_image(game->mlx, "images/wall.xpm", &size_s,
	// 		&size_s);
	// game->e_img = mlx_xpm_file_to_image(game->mlx, "images/empty.xpm", &size_s,
	// 		&size_s);
	load_win_texture(game);
	load_texture(game, &game->img_no, "NO", "images/no.xpm");
	load_texture(game, &game->img_so, "SO", "images/so.xpm");
	load_texture(game, &game->img_we, "WE", "images/we.xpm");
	load_texture(game, &game->img_ea, "EA", "images/ea.xpm");
	create_map_img(game);
	create_mini_map_img(game);
	return (0);
}
