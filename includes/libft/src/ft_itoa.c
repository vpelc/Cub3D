/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:47:11 by dbajeux           #+#    #+#             */
/*   Updated: 2024/07/30 15:04:12 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	count_size_malloc(int c)
{
	int	count;

	count = 0;
	if (c < 1)
		count++;
	while (c)
	{
		c /= 10;
		count++;
	}
	return (count);
}

static void	ft_fill_res(int len, int offset, int c, char *str)
{
	while (len > offset)
	{
		str[len - 1] = c % 10 + '0';
		c /= 10;
		len--;
	}
}

char	*ft_itoa(int c)
{
	char *res;
	int len;
	int offset;

	len = count_size_malloc(c);
	offset = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (c == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		c = 147483648;
		offset = 2;
	}
	if (c < 0)
	{
		res[0] = '-';
		offset = 1;
		c = -c;
	}
	ft_fill_res(len, offset, c, res);
	res[len] = '\0';
	return (res);
}