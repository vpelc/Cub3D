/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:02:46 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/24 16:20:01 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_putnbr(long int nb, int count)
{
	if (nb < 0)
	{
		count = ft_putchar('-', count);
		nb *= -1;
	}
	if (nb > 9)
	{
		count = ft_putnbr(nb / 10, count);
		count = ft_putnbr(nb % 10, count);
	}
	else
		count = ft_putchar(nb + 48, count);
	return (count);
}
