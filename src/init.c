/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:36:09 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/26 14:49:19 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_texinfo(t_game *game)
{
	game->texinfo = ft_malloc(game, sizeof(t_texinfo), 1);
	if (!game->texinfo)
		return (exit_prog("Error : Malloc init_texinfo\n", 1, game));
	game->texinfo->no_path = NULL;
	game->texinfo->so_path = NULL;
	game->texinfo->we_path = NULL;
	game->texinfo->ea_path = NULL;
	game->texinfo->floor[0] = -1;
	game->texinfo->floor[1] = -1;
	game->texinfo->floor[2] = -1;
	game->texinfo->ceiling[0] = -1;
	game->texinfo->ceiling[1] = -1;
	game->texinfo->ceiling[2] = -1;
	game->texinfo->hex_floor = 0x0;
	game->texinfo->hex_ceiling = 0x0;
	game->texinfo->floor_check = FALSE;
	game->texinfo->ceilling_check = FALSE;
}

static void	get_player_dir(t_game *game)
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
	game->player->posa = 0;
	get_player_dir(game);
	game->player->posdx = cos(game->player->posa) * 5;
	game->player->posdy = sin(game->player->posa) * 5;
	game->player->posdxp = cos(game->player->posa + (90 * RAD_DEG)) * 5;
	game->player->posdyp = sin(game->player->posa + (90 * RAD_DEG)) * 5;
}

void	init_texture(t_game *game)
{
	load_win_texture(game);
	convert_map(game);
	load_texture(game, &game->img_no, "NO", game->texinfo->no_path);
	load_texture(game, &game->img_so, "SO", game->texinfo->so_path);
	load_texture(game, &game->img_we, "WE", game->texinfo->we_path);
	load_texture(game, &game->img_ea, "EA", game->texinfo->ea_path);
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
