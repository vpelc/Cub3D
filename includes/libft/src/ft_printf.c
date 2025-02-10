/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:34:15 by dbajeux           #+#    #+#             */
/*   Updated: 2024/07/30 15:05:10 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_print_type(char to_test, unsigned int count, va_list arg)
{
	if (to_test == 'c')
		return (ft_putchar(va_arg(arg, int), count));
	else if (to_test == 's')
		return (ft_putstr(va_arg(arg, char *), count));
	else if (to_test == 'p')
		return (ft_putadress(va_arg(arg, void *), count));
	else if (to_test == 'd' || to_test == 'i')
		return (ft_putnbr(va_arg(arg, int), count));
	else if (to_test == 'u')
		return (ft_putunsigned(va_arg(arg, unsigned int), count));
	else if (to_test == 'x')
		return (ft_puthex(va_arg(arg, unsigned), "0123456789abcdef", count));
	else if (to_test == 'X')
		return (ft_puthex(va_arg(arg, unsigned), "0123456789ABCDEF", count));
	else if (to_test == '%')
		return (ft_putchar('%', count));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list arg;
	int count;
	int i;

	i = 0;
	count = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%' && ft_strchr_printf("cspdiuxX%", str[i + 1]))
		{
			count = ft_print_type(str[i + 1], count, arg);
			i++;
		}
		else if (str[i] != '%')
			count = ft_putchar(str[i], count);
		i++;
	}
	va_end(arg);
	return (count);
}