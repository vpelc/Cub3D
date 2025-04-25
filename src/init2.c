/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:44:34 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/24 16:45:52 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
