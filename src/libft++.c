/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft++.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:23:15 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/26 13:11:24 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup_list(t_game *game, const char *s1)
{
	int		i;
	char	*s1_dup;

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

char	*ft_substr_list(t_game *game, char const *s, unsigned int start,
		size_t len)
{
	char	*substr;

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

