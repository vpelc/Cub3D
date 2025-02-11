/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:27:45 by dbajeux           #+#    #+#             */
/*   Updated: 2024/07/30 15:05:13 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putadress(void *format, int count)
{
	unsigned long nb;
	const char *base = "0123456789abcdef";

	nb = (unsigned long)format;
	count = ft_putstr("0x", count);
	count = ft_puthex(nb, base, count);
	return (count);
}