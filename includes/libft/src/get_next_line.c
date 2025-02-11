/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:32:31 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/10 16:47:42 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	*ft_fill_buff(char *buffer, int fd)
{
	char	*read_buffer;
	int		read_count;

	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (ft_free_gnl(&buffer), NULL);
	while (buffer && !(ft_strchr_gnl(buffer)))
	{
		read_count = read(fd, read_buffer, BUFFER_SIZE);
		if (read_count == -1)
			return (ft_free_gnl(&buffer), ft_free_gnl(&read_buffer), NULL);
		if (read_count == 0)
			break ;
		read_buffer[read_count] = '\0';
		buffer = ft_strjoin_gnl(buffer, read_buffer);
	}
	return (ft_free_gnl(&read_buffer), buffer);
}

static char	*ft_fill_line(char *buffer)
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
	line = malloc(sizeof(char) * (i + 1));
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

static char	*ft_fill_nextbuff(char *buffer)
{
	char	*next_buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buffer || !buffer[i])
		return (ft_free_gnl(&buffer), NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		j++;
	next_buffer = malloc(ft_strlen(buffer) - i + j);
	if (!next_buffer)
		return (ft_free_gnl(&buffer), NULL);
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
		next_buffer[j++] = buffer[i++];
	next_buffer[j] = '\0';
	ft_free_gnl(&buffer);
	return (next_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || (BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647))
		return (ft_free_gnl(&buffer), NULL);
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = ft_fill_buff(buffer, fd);
	if (!buffer)
		return (NULL);
	line = ft_fill_line(buffer);
	buffer = ft_fill_nextbuff(buffer);
	if (!(ft_strchr_gnl(line)))
		ft_free_gnl(&buffer);
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*s;

	fd = open("test", O_RDONLY);
	while ((s = get_next_line(FD_COPY)) != NULL)
	{
		printf("%s", s);
		free(s);
	}
	return (0);
} */