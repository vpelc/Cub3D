/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:55:52 by dbajeux           #+#    #+#             */
/*   Updated: 2024/07/30 15:04:18 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *to_add)
{
	t_list	*tmp;

	if (!lst || !to_add)
		return ;
	tmp = *lst;
	(*lst) = to_add;
	(*lst)->next = tmp;
}