/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:51:30 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/25 13:56:28 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static void	free_img(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img_ea->texture->img);
	mlx_destroy_image(game->mlx, game->img_no->texture->img);
	mlx_destroy_image(game->mlx, game->img_so->texture->img);
	mlx_destroy_image(game->mlx, game->img_we->texture->img);
	mlx_destroy_image(game->mlx, game->win_img->img);
	mlx_destroy_image(game->mlx, game->map_img->img);
	mlx_destroy_image(game->mlx, game->minimap_img->img);
}

int	close_window(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	free_img(game);
	mlx_destroy_window(game->mlx, game->win);
	free_list(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (1);
}
