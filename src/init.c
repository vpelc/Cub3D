/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:36:09 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/16 11:21:34 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_texinfo(t_game *game)
{
	// game->texinfo = malloc(sizeof(t_texinfo));
	game->texinfo = ft_malloc(game, sizeof(t_texinfo), 1);
	if (!game->texinfo)
		return (exit_prog("Error : Malloc init_texinfo\n", 1,game));
	game->texinfo->NO_path = NULL;
	game->texinfo->SO_path = NULL;
	game->texinfo->WE_path = NULL;
	game->texinfo->EA_path = NULL;
	game->texinfo->floor[0] = -1;
	game->texinfo->floor[1] = -1;
	game->texinfo->floor[2] = -1;
	game->texinfo->ceiling[0] = -1;
	game->texinfo->ceiling[1] = -1;
	game->texinfo->ceiling[2] = -1;
	game->texinfo->hex_floor = 0x0;
	game->texinfo->hex_ceiling = 0x0;
}

void	get_player_dir(t_game *game)
{
	if (game->texinfo->dir == 'N')
		game->player->posa = 270 * RAD_DEG;
	if (game->texinfo->dir == 'S')
		game->player->posa = 90 * RAD_DEG;
	if (game->texinfo->dir == 'E')
		game->player->posa = 0 * RAD_DEG;
	if (game->texinfo->dir == 'W')
		game->player->posa = 180 * RAD_DEG;
}

void	init_player(t_game *game)
{
	get_player_dir(game);
	game->player->posa = 0;
	game->player->posdx = cos(game->player->posa) * 5;
	game->player->posdy = sin(game->player->posa) * 5;
	game->player->posdxp = cos(game->player->posa + (90 * RAD_DEG)) * 5;
	game->player->posdyp = sin(game->player->posa + (90 * RAD_DEG)) * 5;
}

void	init_texture(t_game *game)
{
	load_win_texture(game);
	convert_map(game);
	load_texture(game, &game->img_no, "NO", game->texinfo->NO_path);
	load_texture(game, &game->img_so, "SO", game->texinfo->SO_path);
	load_texture(game, &game->img_we, "WE", game->texinfo->WE_path);
	load_texture(game, &game->img_ea, "EA", game->texinfo->EA_path);
	create_map_img(game);
	create_mini_map_img(game);
}

void	init_keys(t_game *game)
{
	t_keys	*keys;

	keys = ft_malloc(game, sizeof(t_keys), 1);
	keys->down_key = 0;
	keys->left_key = 0;
	keys->right_key = 0;
	keys->up_key = 0;
	keys->rotl_key = 0;
	keys->rotr_key = 0;
	keys->shift_key = 0;
	game->keys = keys;
}

int	init_game(t_game *game)
{
	t_map		*map;
	t_player	*player;

	game->to_free = NULL;
	player = ft_malloc(game, sizeof(t_player), 1);
	game->player = player;
	map = ft_malloc(game, sizeof(t_map), 1);
	game->map = map;
	game->map->width = 0;
	init_texinfo(game);
	init_keys(game);
	return (0);
}
