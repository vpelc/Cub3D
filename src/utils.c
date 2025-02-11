/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:38:04 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/11 14:03:12 by vpelc            ###   ########.fr       */
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
	new_ptr->content = ptr;
	new_ptr->next = tmp;
	game->to_free = new_ptr;
	return (ptr);
}

int	close_window(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	// free all
	
	return 1;
}
