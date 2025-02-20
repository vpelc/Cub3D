/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 00:50:51 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/20 21:39:15 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_max_line_infile(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		i++;
		free(line);
	}
	return (i);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (TRUE);
	else
		return (FALSE);
}
void free_tab(char **tab)
{
	int i;

	i= 0;
	if(!tab)
		return;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
}