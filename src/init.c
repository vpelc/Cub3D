/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:36:09 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/11 14:03:32 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	fake_init_map(t_map *map)
{
	char	**tab;
	int		i;
	
	i = -1;
	tab = ft_malloc(map->game, sizeof(char *), 9);
	if (!tab)
		return (1);
	while (++i < 8)
		tab[i] = ft_malloc(map->game, sizeof(char), 9);
	tab[i] = NULL;
	tab[0] = "11111111";
	tab[1] = "10011001";
	tab[2] = "10011001";
	tab[3] = "10000001";
	tab[4] = "10000001";
	tab[5] = "11001001";
	tab[6] = "11011001";
	tab[7] = "11111111";
	map->tab = tab;
	return (0);
}

int	init_game(t_game *game)
{
	t_player	*player;
	t_map		*map;
	t_keys		*keys;

	player = ft_malloc(game, sizeof(t_player *), 1);
	keys = ft_malloc(game, sizeof(t_keys *), 1);
	map = ft_malloc (game, sizeof(t_map *), 1);
	player->game = game;
	game->player = player;
	map->game = game;
	game->map = map;
	player->posx = 300; 							//change to proper value
	player->posy = 300;								//same
	keys->down_key = 0;
	keys->left_key = 0;
	keys->right_key = 0;
	keys->up_key = 0;
	fake_init_map(map);
}