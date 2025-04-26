/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:23:15 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/26 13:10:38 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_malloc(t_game *game, size_t size, size_t count)
{
	void	*ptr;
	t_free	*tmp;
	t_free	*new_ptr;
	size_t	buff;

	buff = count * size;
	if (buff > INT_MAX || (size != 0 && (buff / size) != count))
		return (NULL);
	ptr = malloc(buff);
	if (!ptr)
		return (NULL);
	tmp = game->to_free;
	new_ptr = malloc(sizeof(t_free) * 1);
	if (!new_ptr)
		return (NULL);
	new_ptr->content = ptr;
	new_ptr->next = tmp;
	game->to_free = new_ptr;
	return (ptr);
}

void	exit_prog(char *msg, int error, t_game *game)
{
	(void)game;
	if (error == 1)
	{
		free_list(game);
		ft_putstr_fd(msg, 2);
		exit(1);
	}
	if (error == 2)
	{
		ft_putstr_fd(msg, 2);
		exit(1);
	}
}
