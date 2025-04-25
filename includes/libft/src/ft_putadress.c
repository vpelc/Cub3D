/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:27:45 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/24 16:19:38 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putadress(void *format, int count)
{
	unsigned long	nb;
	const char		*base = "0123456789abcdef";

	nb = (unsigned long)format;
	count = ft_putstr("0x", count);
	count = ft_puthex(nb, base, count);
	return (count);
}
