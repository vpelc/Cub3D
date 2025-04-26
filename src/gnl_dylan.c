/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_dylan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:07:27 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/26 16:08:06 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_free_dylan(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_clean_storage_dylan(char *storage)
{
	char	*breakpoint;
	char	*new_storage;
	int		len;

	breakpoint = ft_strchr_dylan(storage, '\n');
	if (!breakpoint)
	{
		new_storage = NULL;
		return (ft_free_dylan(&storage));
	}
	else
		len = (breakpoint - storage) + 1;
	if (!storage[len])
		return (ft_free_dylan(&storage));
	new_storage = ft_substr_dylan(storage, len, ft_strlen_dylan(storage) - len);
	ft_free_dylan(&storage);
	return (new_storage);
}

char	*ft_clean_line_dylan(char *storage)
{
	char	*line;
	char	*breakpoint;
	int		len;

	breakpoint = ft_strchr_dylan(storage, '\n');
	len = (breakpoint - storage + 1);
	line = ft_substr_dylan(storage, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_fill_storage_dylan(int fd, char *storage)
{
	int		readcheck;
	char	*buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free_dylan(&storage));
	readcheck = 1;
	buffer[0] = '\0';
	while (readcheck > 0 && !ft_strchr_dylan(buffer, '\n'))
	{
		readcheck = read(fd, buffer, BUFFER_SIZE);
		if (readcheck > 0)
		{
			buffer[readcheck] = '\0';
			storage = ft_strjoin_dylan(storage, buffer);
		}
	}
	free(buffer);
	if (readcheck == -1)
		return (ft_free_dylan(&storage));
	return (storage);
}

char	*get_next_line_dylan(int fd)
{
	static char	*storage = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if ((storage && !ft_strchr_dylan(storage, '\n')) || !storage)
		storage = ft_fill_storage_dylan(fd, storage);
	if (!storage)
		return (NULL);
	line = ft_clean_line_dylan(storage);
	if (!line)
		return (ft_free_dylan(&storage));
	storage = ft_clean_storage_dylan(storage);
	return (line);
}
