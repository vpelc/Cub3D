/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:50:33 by dbajeux           #+#    #+#             */
/*   Updated: 2024/07/30 15:05:35 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_puthex(unsigned long int nb, const char *base, int count)
{
	if (nb > ft_strlen(base) - 1)
		count = ft_puthex(nb / ft_strlen(base), base, count);
	count = ft_putchar(*(base + (nb % ft_strlen(base))), count);
	return (count);
}