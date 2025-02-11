/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:56:53 by dbajeux           #+#    #+#             */
/*   Updated: 2024/07/30 15:06:13 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
			{
				i++;
			}
		}
		else if (s[i] && s[i] == c)
		{
			i++;
		}
	}
	return (count);
}

static size_t	ft_word_len(char const *s, char c, size_t start)
{
	size_t	i;

	i = 0;
	while (s[start] && s[start] != c)
	{
		i++;
		start++;
	}
	return (i);
}

static void	free_array(size_t size, char **array)
{
	size_t	i;

	i = 0;
	while (size > 0)
	{
		free(array[i]);
		size--;
		i++;
	}
	free(array);
}

static char	**split(char const *s, char c, size_t word_number, char **array)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (i < word_number)
	{
		while (s[j] && s[j] == c)
			j++;
		array[i] = ft_substr(s, j, ft_word_len(s, c, j));
		if (!(array[i]))
		{
			free_array(i, array);
			return (NULL);
		}
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	word_number;

	if (!s)
		return (NULL);
	word_number = ft_count_word(s, c);
	array = malloc(sizeof(char *) * (word_number + 1));
	if (!array)
		return (NULL);
	array = split(s, c, word_number, array);
	return (array);
}