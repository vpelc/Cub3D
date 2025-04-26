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

#include "../../includes/cub3d.h"

char	*ft_strjoin_gnl_list(t_game *game, char *buffer, char *read_buffer)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!buffer || !read_buffer)
		return (ft_free_gnl(&read_buffer), NULL);
	join = ft_malloc(game, sizeof(char), (ft_strlen_gnl(buffer)
				+ ft_strlen_gnl(read_buffer) + 1));
	if (!join)
		return (NULL);
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
	return (join);
}


