/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:51:11 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/24 16:20:26 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putunsigned(unsigned int nb, int count)
{
	if (nb > 9)
	{
		count = ft_putnbr(nb / 10, count);
		count = ft_putnbr(nb % 10, count);
	}
	else
		count = ft_putchar(nb + 48, count);
	return (count);
}
