/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:34:04 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/27 16:38:16 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (TRUE);
	else
		return (FALSE);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	count_line_map(int fd)
{
	char *line;
	int map_number_line;

	line = NULL;
	map_number_line = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (check_line_contain_map(line) == TRUE)
			map_number_line++;
		free(line);
		continue ;
	}
	close(fd);
	return (map_number_line);
}

int	check_tab_empty(int tab[3])
{
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1)
		return (FALSE);
	return (TRUE);
}

char	*identify_flag(char *line)
{
	const char	*flags[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (ft_isspace(line[i]) == TRUE)
		i++;
	while (flags[j])
	{
		if (!ft_strncmp(&line[i], flags[j], ft_strlen(flags[j])))
			return ((char *)flags[j]);
		j++;
	}
	return (NULL);
}