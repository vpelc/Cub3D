/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:46:54 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/25 13:20:05 by dbajeux          ###   ########.fr       */
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

int	is_valid_index(int index)
{
	return (index >= 0 && index <= 2);
}

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
}
