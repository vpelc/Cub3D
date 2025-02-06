/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:32:19 by vpelc             #+#    #+#             */
/*   Updated: 2024/06/04 15:32:20 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *c)
{
	size_t	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *buffer, char *read_buffer)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!buffer || !read_buffer)
		return (ft_free(&buffer), ft_free(&read_buffer), NULL);
	join = malloc((ft_strlen(buffer) + ft_strlen(read_buffer) + 1));
	if (!join)
		return (ft_free(&buffer), NULL);
	i = 0;
	while (buffer && buffer[i])
	{
		join[i] = buffer[i];
		i++;
	}
	j = 0;
	while (buffer && read_buffer[j])
	{
		join[i + j] = read_buffer[j];
		j++;
	}
	join[i + j] = '\0';
	return (ft_free(&buffer), join);
}

int	ft_strchr(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

void	ft_free(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
}