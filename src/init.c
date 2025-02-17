/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:24:36 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/17 15:10:18 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_texinfo(t_game *game)
{
	game->texinfo = malloc(sizeof(t_texinfo));
	if (!game->texinfo)
		return (ft_putstr_fd("Error : Mallox init_texinfo\n",2));
	game->texinfo->NO_path = NULL;
	game->texinfo->SO_path = NULL;
	game->texinfo->WE_path = NULL;
	game->texinfo->EA_path = NULL;
	game->texinfo->floor[0] = 0;
	game->texinfo->floor[1] = 0;
	game->texinfo->floor[2] = 0;
	game->texinfo->ceiling[0] = 0;
	game->texinfo->ceiling[1] = 0;
	game->texinfo->ceiling[2] = 0;
	game->texinfo->hex_floor = 0x0;
	game->texinfo->hex_ceiling = 0x0;
}

static void	init_mapinfo(t_game *game)
{
	game->mapinfo = malloc(sizeof(t_mapinfo));
	if (!game->mapinfo)
		return (ft_putstr_fd("Error : Malloc init_mapinfo\n",2));
	game->mapinfo->fd = 0;
    game->mapinfo->index_file = 0;
    game->mapinfo->num_max_line_file = 0;
}
void	init_data(t_game *game)
{
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error : Malloc init_data",2));
	game->mlx = NULL;
	game->win = NULL;
	init_mapinfo(game);
	init_texinfo(game);
}