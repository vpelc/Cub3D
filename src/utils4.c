/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:57:44 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/25 13:22:53 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_rgb(char *path, int index)
{
	char	**values;
	char	*trimmed;
	int		result;

	if (!is_valid_index(index))
		return (-1);
	values = ft_split(path, ',');
	if (!values)
		return (-1);
	if (!values[0] || !values[1] || !values[2] || values[3])
		return (free_tab(values), -1);
	trimmed = ft_strtrim(values[index], " \t\n");
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		return (free_tab(values), -1);
	}
	result = ft_atoi(trimmed);
	free(trimmed);
	free_tab(values);
	return (result);
}

void	fill_map(char *line, t_game *game)
{
	int		i;
	char	*str_trim;

	i = 0;
	str_trim = NULL;
	while (game->map->tab[i])
		i++;
	str_trim = ft_strtrim_list(game, line, "\n");
	game->map->tab[i] = ft_strdup_list(game, str_trim);
	game->map->tab[i + 1] = NULL;
}

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
