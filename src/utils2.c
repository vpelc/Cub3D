/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:40:39 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/25 13:50:52 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_pos_y_player(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
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

int	get_pos_x_player(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
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

int	convert_map(t_game *game)
{
	char	**cv_map;
	int		i;

	cv_map = ft_malloc(game, sizeof(char *), (game->map->height + 1));
	if (!cv_map)
		return (FALSE);
	i = 0;
	while (i < game->map->height)
	{
		cv_map[i] = ft_malloc(game, sizeof(char), (game->map->width + 1));
		if (!cv_map[i])
			return (FALSE);
		ft_memset(cv_map[i], ' ', game->map->width);
		cv_map[i][game->map->width] = '\0';
		ft_strcpy(cv_map[i], game->map->tab[i]);
		i++;
	}
	game->map->cv_tab = cv_map;
	return (TRUE);
}
