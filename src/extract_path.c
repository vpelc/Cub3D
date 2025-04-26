/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:28:59 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/26 15:06:29 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_rgb_values(char **values)
{
	int		i;
	int		j;
	int		num;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (values[i][++j])
		{
			if (values[i][j] == '\n')
				continue ;
			if (!ft_isdigit(values[i][j]))
				return (free_tab(values), -1);
		}
		num = ft_atoi(values[i]);
		if (num < 0 || num > 255)
			return (free_tab(values), -1);
	}
	free_tab(values);
	return (TRUE);
}

static int	is_valid_rgb_format(char *line)
{
	char	**values;
	int		i;
	char	*trimmed;

	if (!line || *line == '\0')
		return (-1);
	values = ft_split(line, ',');
	if (!values)
		return (-1);
	i = 0;
	while (values[i])
	{
		trimmed = ft_strtrim(values[i], " \t\n");
		free(values[i]);
		values[i] = trimmed;
		i++;
	}
	if (i != 3)
		return (free_tab(values), -1);
	return (validate_rgb_values(values));
}

static char	*extract_colour(t_game *game, char *line)
{
	int	i;
	int	start;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'F' || line[i] == 'C')
		i++;
	while (ft_isspace(line[i]))
		i++;
	start = i;
	if (is_valid_rgb_format(line + start) == -1)
	{
		line = NULL;
		exit_prog("Error: Invalid RGB format.\n", 1, game);
	}
	return (ft_strdup_list(game, line + start));
}

static char	*extract_texture(t_game *game, char *line)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	path = ft_strtrim_list(game, line + i, " \t\n");
	j = 0;
	while (path[j])
	{
		if (ft_isspace(path[j]))
		{
			free(path);
			exit_prog("Error: Invalid texture path, spaces are not allowed.\n",
				1, game);
		}
		j++;
	}
	return (path);
}

char	*extract_path(t_game *game, char *line, char *flag)
{
	if (!ft_strncmp(flag, "NO", 3) || !ft_strncmp(flag, "SO", 3)
		|| !ft_strncmp(flag, "WE", 3) || !ft_strncmp(flag, "EA", 3))
		return (extract_texture(game, line));
	else if (!ft_strncmp(flag, "F", 2) || !ft_strncmp(flag, "C", 2))
	{
		return (extract_colour(game, line));
	}
	else
		return (NULL);
}
