/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:38:15 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/25 12:01:58 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	define_size_x_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->tab[i])
	{
		j = 0;
		while (game->map->tab[i][j])
			j++;
		if (game->map->width < j)
			game->map->width = j;
		i++;
	}
}

void	check_double_pos_start(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = -1;
	while (game->map->tab[i])
	{
		j = 0;
		while (game->map->tab[i][j])
		{
			if (game->map->tab[i][j] == 'N' || game->map->tab[i][j] == 'S'
				|| game->map->tab[i][j] == 'E' || game->map->tab[i][j] == 'W')
			{
				if (flag == 1)
					exit_prog("Error: Found mutilple start pos.\n", 1, game);
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (flag == -1)
		exit_prog("Error: no start pos in Map.\n", 1, game);
}

static void	flood_fill(char **map, int x, int y, t_game *game)
{
	if ((x < 0 || y < 0) || (x >= (int)ft_strlen(map[y])
			|| y >= (game->map->height) || map[y][x] == ' '))
	{
		free_tab(map);
		exit_prog("Error: Invalid Map.\n", 1, game);
	}
	if (map[y][x] == '1' || map[y][x] == 'x')
		return ;
	map[y][x] = 'x';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

void	check_map_fully_enclosed(t_game *game)
{
	char	**map_copy;
	int		start_y;
	int		start_x;

	map_copy = copy_map(game->map->tab, game->map->height);
	if (!map_copy)
		exit_prog("Error: malloc copy map.\n", 1, game);
	start_y = get_pos_y_player(map_copy);
	start_x = get_pos_x_player(map_copy);
	game->player->posy = (start_y * 64) + 32;
	game->player->posx = (start_x * 64) + 32;
	flood_fill(map_copy, start_x, start_y, game);
	game->texinfo->dir = game->map->tab[start_y][start_x];
	game->map->tab[start_y][start_x] = '0';
	free_tab(map_copy);
}
