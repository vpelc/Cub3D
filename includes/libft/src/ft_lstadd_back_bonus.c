/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:50:28 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/24 16:17:26 by dbajeux          ###   ########.fr       */
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
