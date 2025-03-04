/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:14:09 by dbajeux           #+#    #+#             */
/*   Updated: 2025/03/04 18:38:49 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_char_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->mapinfo->map[i])
	{
		j = 0;
		while (game->mapinfo->map[i][j])
		{
			if (game->mapinfo->map[i][j] != '0'
				&& game->mapinfo->map[i][j] != '1'
				&& game->mapinfo->map[i][j] != 'N'
				&& game->mapinfo->map[i][j] != 'S'
				&& game->mapinfo->map[i][j] != 'E'
				&& game->mapinfo->map[i][j] != 'W'
				&& !ft_isspace(game->mapinfo->map[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	check_double_pos_start(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = -1;
	while (game->mapinfo->map[i])
	{
		j = 0;
		while (game->mapinfo->map[i][j])
		{
			if (game->mapinfo->map[i][j] == 'N'
				|| game->mapinfo->map[i][j] == 'S'
				|| game->mapinfo->map[i][j] == 'E'
				|| game->mapinfo->map[i][j] == 'W')
			{
				if (flag == 1)
					return (ft_putstr_fd("Error : Found mutilple start pos\n",
							2), FALSE);
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (flag == -1)
		return (ft_putstr_fd("Error : no start pos in Map\n", 2), FALSE);
	return (TRUE);
}

int	get_map_width(char **map)
{
	int	max_width;
	int	width;
	int	i;

	i = 0;
	max_width = 0;
	width = 0;
	while (map[i])
	{
		width = ft_strlen(map[i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	return (max_width);
}

int	fill_flood(char **map, int x, int y, int max_y)
{
	
}



int	check_flood(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] != '1' && map[y][x] != 'F')
				return (FALSE);
			x++;
		}
		y++;
	}
	return (TRUE);
}

char	**copy_map(char **map, int height)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	while (i < height)
	{
		new_map[i] = ft_strdup(map[i]);
		i++;
	}
	new_map[height] = NULL;
	return (new_map);
}

int	get_pos_x_player(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while ((map[i][j]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S')
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

int	get_pos_y_player(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while ((map[i][j]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	check_map_fully_enclosed(t_game *game)
{
	char **map_copy;
	int max_y;
	int is_open;
	map_copy = copy_map(game->mapinfo->map, game->mapinfo->map_number_line);
	max_y = game->mapinfo->map_number_line;
	if (!map_copy)
		return (ft_putstr_fd("Error : malloc copy map\n", 2), FALSE);
	is_open = fill_flood(map_copy, get_pos_x_player(map_copy),
			get_pos_y_player(map_copy),max_y);
	if (is_open)
	
	if (check_flood(map_copy) == FALSE)
	{
		free_tab(map_copy);
		return (ft_putstr_fd("Error map not fully enclosed", 2), FALSE);
	}
	free_tab(map_copy);
	return (TRUE);
}