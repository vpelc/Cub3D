/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:38:04 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/20 13:54:54 by vpelc            ###   ########.fr       */
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

void	free_list(t_game *game)
{
	t_free	*tmp;
	t_free	*list;

	list = game->to_free;
	while (list != NULL)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}

int	close_window(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	// free_list(game);
	return (1);
}
