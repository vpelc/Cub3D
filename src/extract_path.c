/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:28:59 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/17 12:30:59 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_rgb_format(char *line)
{
	char	**values;
	int		i;
	int		j;
	int		num;
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
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (values[i][j])
		{
			if (values[i][j] == '\n')
			{
				j++;
				continue ;
			}
			if (!ft_isdigit(values[i][j]))
				return (free_tab(values), -1);
			j++;
		}
		num = ft_atoi(values[i]);
		if (num < 0 || num > 255)
			return (free_tab(values), -1);
		i++;
	}
	free_tab(values);
	return (TRUE);
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
		exit_prog("Error: Invalid RGB format.\n", 2,game);
	return (ft_strdup_list(game, line + start));
}

static char	*extract_texture(t_game *game, char *line)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	end = i - 1;
	return (ft_substr_list(game, line, start, end - start + 1));
}

char	*extract_path(t_game *game, char *line, char *flag)
{
	// int	i;

	// i = 0;
	// while (ft_isspace(line[i]) == TRUE)
	// 	i++;
	if (!ft_strncmp(flag, "NO", 3) || !ft_strncmp(flag, "SO", 3)
		|| !ft_strncmp(flag, "WE", 3) || !ft_strncmp(flag, "EA", 3))
		return (extract_texture(game, line));
	// else if (flag[i] == 'F' || flag[i] == 'C')
	// {
	// 	return (extract_colour(game, line));
	// }
	else if (!ft_strncmp(flag, "F", 2) || !ft_strncmp(flag, "C", 2))
	{
		return (extract_colour(game, line));
	}
	else
		return (NULL);
}
