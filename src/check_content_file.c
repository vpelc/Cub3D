/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:52:50 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/17 15:27:10 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_empty_file(int fd)
{
	char	buffer[1];

	if (read(fd, buffer, 1) <= 0)
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

// static void	init_check_bool(int *tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		tab[i] = 0;
// 		i++;
// 	}
// }

static int	is_empty_line(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (ft_issspasce(str[i]) == FALSE)
			check = 1;
		i++;
	}
	if (check == 1)
		return (FALSE);
	else
		return (TRUE);
}
static int	check_texture(int fd)
{
	char	*line;

	line = NULL;
	while (is_empty_line(line) == TRUE)
		line = get_next_line(fd);
	free(line);
	return (TRUE);
}

int	check_content_file(t_game *game)
{
  
	if (check_empty_file(game->mapinfo->fd) == FALSE)
	{
		ft_putstr_fd("Error: File empty\n", 2);
		return (FALSE);
	}
	if (check_texture(game->mapinfo->fd) == FALSE)
		return (FALSE);
	return (TRUE);
}