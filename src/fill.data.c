/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:36:56 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/19 12:42:45 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	fill_data(t_game *game)
{
	char *line;
	game->mapinfo->num_max_line_file = get_max_line_infile(game->mapinfo->fd);
	while ((line = get_next_line(game->mapinfo->fd)) != NULL)
	{
	}
}