/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:20:15 by dbajeux           #+#    #+#             */
/*   Updated: 2025/03/07 14:26:00 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	fill_hexa(t_game *game)
{
	game->texinfo->hex_floor = rgb_to_hex(game->texinfo->floor[0],
			game->texinfo->floor[1], game->texinfo->floor[2]);
	game->texinfo->hex_ceiling = rgb_to_hex(game->texinfo->ceiling[0],
			game->texinfo->ceiling[1], game->texinfo->ceiling[2]);
	if (game->texinfo->hex_ceiling == 0x0 || game->texinfo->hex_floor == 0x0)
		return (FALSE);
	else
		return (TRUE);
}

static int	parse_rgb(char *path, int index)
{
	char	**values;
	int		result;

	values = ft_split(path, ',');
	if (!values)
		return (-1);
	result = ft_atoi(values[index]);
	free_tab(values);
	return (result);
}

static int	fill_color_data(char *flag, char *path, t_game *game)
{
	if (flag[0] == 'F')
	{
		game->texinfo->floor[0] = parse_rgb(path, 0);
		game->texinfo->floor[1] = parse_rgb(path, 1);
		game->texinfo->floor[2] = parse_rgb(path, 2);
	}
	else if (flag[0] == 'C')
	{
		game->texinfo->ceiling[0] = parse_rgb(path, 0);
		game->texinfo->ceiling[1] = parse_rgb(path, 1);
		game->texinfo->ceiling[2] = parse_rgb(path, 2);
	}
	else
		return (FALSE);
	if (fill_hexa(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	fill_texture(char *path, char *flag, t_game *game)
{
	if (!ft_strncmp(flag, "NO", 3))
		game->texinfo->NO_path = path;
	else if (!ft_strncmp(flag, "SO", 3))
		game->texinfo->SO_path = path;
	else if (!ft_strncmp(flag, "WE", 3))
		game->texinfo->WE_path = path;
	else if (!ft_strncmp(flag, "EA", 3))
		game->texinfo->EA_path = path;
	else if (flag[0] == 'C' || flag[0] == 'F')
		return (fill_color_data(flag, path, game));
	else
		return (FALSE);
	return (TRUE);
}

void	fill_map(char *line, t_game *game)
{
	int		i;
	char	*str_trim;

	i = 0;
	str_trim = NULL;
	while (game->map->tab[i])
		i++;
	str_trim = ft_strtrim(line, "\n");
	game->map->tab[i] = ft_strdup(str_trim);
	game->map->tab[i + 1] = NULL;
}
