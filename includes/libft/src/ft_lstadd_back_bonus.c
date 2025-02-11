/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:50:28 by dbajeux           #+#    #+#             */
/*   Updated: 2024/07/30 15:04:15 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *to_add)
{
	if (!lst || !to_add)
		return ;
	else if (!*lst)
	{
		*lst = to_add;
		return ;
	}
	ft_lstlast(*lst)->next = to_add;
}