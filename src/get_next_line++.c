/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line++.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:32:31 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/26 14:59:56 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*ft_fill_buff(t_game *game, char *buffer, int fd)
{
	char	*read_buffer;
	int		read_count;

	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (NULL);
	while (buffer && !(ft_strchr_gnl(buffer)))
	{
		read_count = read(fd, read_buffer, BUFFER_SIZE);
		if (read_count == -1)
			return (ft_free_gnl(&read_buffer), NULL);
		if (read_count == 0)
			break ;
		read_buffer[read_count] = '\0';
		buffer = ft_strjoin_gnl_list(game, buffer, read_buffer);
	}
	return (ft_free_gnl(&read_buffer), buffer);
}

static char	*ft_fill_line(t_game *game, char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_malloc(game, sizeof(char), (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_fill_nextbuff(t_game *game, char *buffer)
{
	char	*next_buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n' || ft_strlen(buffer) - i + j == 0)
		j++;
	next_buffer = ft_malloc(game, sizeof(char), ft_strlen(buffer) - i + j);
	if (!next_buffer)
		return (NULL);
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
		next_buffer[j++] = buffer[i++];
	next_buffer[j] = '\0';
	// ft_free_gnl(&buffer);
	return (next_buffer);
}

char	*get_next_line_list(int fd, t_game *game)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || (BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647))
		return (NULL);
	if (!buffer)
	{
		buffer = ft_malloc(game, sizeof(char), 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = ft_fill_buff(game, buffer, fd);
	if (!buffer)
		return (NULL);
	line = ft_fill_line(game, buffer);
	buffer = ft_fill_nextbuff(game, buffer);
	// if (!(ft_strchr_gnl(line)))
	// 	ft_free_gnl(&buffer);
	return (line);
}
