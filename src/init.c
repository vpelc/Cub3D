/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:36:09 by vpelc             #+#    #+#             */
/*   Updated: 2025/03/07 14:22:38 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_texinfo(t_game *game)
{
	game->texinfo = malloc(sizeof(t_texinfo));
	if (!game->texinfo)
		return (ft_putstr_fd("Error : Mallox init_texinfo\n", 2));
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
	t_player	*player;

	player = ft_malloc(game, sizeof(t_player), 1);
	game->player = player;
	get_player_dir(game);
	// player->posa = 2 * PI;
	player->posdx = cos(player->posa) * 5;
	player->posdy = sin(player->posa) * 5;
	game->player->posdxp = cos(game->player->posa + (90 * RAD_DEG)) * 5;
	game->player->posdyp = sin(game->player->posa + (90 * RAD_DEG)) * 5;
}

void	init_texture(t_game *game)
{
	load_win_texture(game);
	load_texture(game, &game->img_no, "NO", "images/no.xpm");
	load_texture(game, &game->img_so, "SO", "images/so.xpm");
	load_texture(game, &game->img_we, "WE", "images/we.xpm");
	load_texture(game, &game->img_ea, "EA", "images/ea.xpm");
	create_map_img(game);
	create_mini_map_img(game);
}

void	init_keys(t_game *game)
{
	t_keys		*keys;
	
	keys = ft_malloc(game, sizeof(t_keys), 1);	
	keys->down_key = 0;
	keys->left_key = 0;
	keys->right_key = 0;
	keys->up_key = 0;
	game->keys = keys;
}

int	init_game(t_game *game)
{
	t_map		*map;
	
	map = ft_malloc(game, sizeof(t_map), 1);
	game->map = map;
	init_texinfo(game);
	init_keys(game);
	return (0);
}
