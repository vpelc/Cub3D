/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:23:58 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/27 16:38:25 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_line_contain_map(char *line)
{
	int	i;

	i = 0;
	if (check_is_empty_line(line) == TRUE || !line)
		return (FALSE);
	while (line[i])
	{
		if (ft_isspace(line[i]) == FALSE && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'S')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_texture_is_fill(t_game *game)
{
	if (!game || !game->texinfo->NO_path || !game->texinfo->SO_path
		|| !game->texinfo->WE_path || !game->texinfo->EA_path)
		return (FALSE);
	if (check_tab_empty(game->texinfo->floor) == FALSE
		|| check_tab_empty(game->texinfo->ceiling) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	check_doublon_flag(char *flag, t_game *game)
{
	if (!flag || !game || !game->texinfo)
		return (FALSE);
	if (!ft_strncmp(flag, "NO", 2) && (game->texinfo->NO_path))
		return (TRUE);
	if (!ft_strncmp(flag, "SO", 2) && (game->texinfo->SO_path))
		return (TRUE);
	if (!ft_strncmp(flag, "WE", 2) && (game->texinfo->WE_path))
		return (TRUE);
	if (!ft_strncmp(flag, "EA", 2) && (game->texinfo->EA_path))
		return (TRUE);
	if (flag[0] == 'F' && (game->texinfo->floor) == 0)
		return (TRUE);
	if (flag[0] == 'C' && (game->texinfo->ceiling) == 0)
		return (TRUE);
	return (FALSE);
}

int	check_line_contain_flag(char *line)
{
	int		i;
	char	**line_tab;
	char	*trimmed_path;

	i = 0;
	trimmed_path = ft_strtrim((const char *)line, " 	\n");
	line_tab = ft_split(trimmed_path, ' ');
	while (line_tab[i])
		i++;
	if (i != 2)
		return (FALSE);
	if (!ft_strncmp(line_tab[0], "NO", 3) || !ft_strncmp(line_tab[0], "SO", 3)
		|| !ft_strncmp(line_tab[0], "WE", 3) || !ft_strncmp(line_tab[0], "EA",
			3) || !ft_strncmp(line_tab[0], "F", 3) || !ft_strncmp(line_tab[0],
			"C", 3))
	{
		return (TRUE);
	}
	else
		return (FALSE);
}

int	check_is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n' || line[0] == '\0')
		return (TRUE);
	while (line[i] && ft_isspace(line[i]) == TRUE)
		i++;
	if (line[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
}
