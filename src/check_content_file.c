/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:52:50 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/19 15:55:25 by dbajeux          ###   ########.fr       */
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

static int	is_texture_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (ft_issspasce(line[i]) == TRUE))
		i++;
	if (line[i] == '\0')
		return (FALSE);
	else
		return (TRUE);
}

static char	*identify_texture(char *line)
{
	int	i;

	i = 0;
	while (ft_issspasce(line[i]) == TRUE)
		line++;
	if (!ft_strncmp(line, 'NO', 2) || !ft_strncmp(line, 'SO', 2)
		|| !ft_strncmp(line, 'WE', 2) || !ft_strncmp(line, 'EA', 2)
		|| !ft_strncmp(line, 'F', 1) || !ft_strncmp(line, 'C', 1))
		return (line);
	else
		return (NULL);
}

static int	fill_texture_data(char *line, char flag, t_game *game)
{
	if (flag == 'N' && !game->texinfo->NO_path)
		game->texinfo->NO_path =
}
static int	check_texture(int fd, t_game *game)
{
	char	*line;
	char	*result;
	char	*flag;

	result = NULL;
	flag = '\0';
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (is_texture_line(line))
		{
			flag = identify_texture(line);
			if (fill_texture_data(line, flag, game) == FALSE)
				return (FALSE);
		}
		free(line);
	}
	return (TRUE);
}

int	check_content_file(t_game *game)
{
	if (check_empty_file(game->mapinfo->fd) == FALSE)
	{
		ft_putstr_fd("Error: File empty\n", 2);
		return (FALSE);
	}
	if (check_texture(game->mapinfo->fd, game) != 6)
		return (FALSE);
	return (TRUE);
}