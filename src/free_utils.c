/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:23:15 by vpelc             #+#    #+#             */
/*   Updated: 2025/03/25 13:32:34 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_malloc(t_game *game, size_t size, size_t count)
{
	void	*ptr;
	t_free	*tmp;
	t_free	*new_ptr;
	size_t	buff;

	buff = count * size;
	if (buff > INT_MAX || (size != 0 && (buff / size) != count))
		return (NULL);
	ptr = malloc(buff);
	if (!ptr)
		return (NULL);
	tmp = game->to_free;
	new_ptr = malloc(sizeof(t_free) * 1);
	if (!new_ptr)
		return (NULL);
	new_ptr->content = ptr;
	new_ptr->next = tmp;
	game->to_free = new_ptr;
	return (ptr);
}

char	*ft_strdup_list(t_game *game, const char *s1)
{
	int i;
	char *s1_dup;

	i = 0;
	while (s1[i])
		i++;
	s1_dup = ft_malloc(game, sizeof(char), (i + 1));
	if (!s1_dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s1_dup[i] = s1[i];
		i++;
	}
	s1_dup[i] = '\0';
	return (s1_dup);
}

char	*ft_substr_list(t_game *game, char const *s, unsigned int start, size_t len)
{
	char *substr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup_list(game, ""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substr = ft_malloc(game, sizeof(char), len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

char	*ft_strtrim_list(t_game *game, char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr_list(game, s1, start, end - start));
}

// void	free_list(t_game *game)
// {
// 	t_free	*tmp;
// 	t_free	*list;

// 	list = game->to_free;
// 	while (list != NULL)
// 	{
// 		tmp = list->next;
// 		free(list->content);
// 		free(list);
// 		list = tmp;
// 	}
// }