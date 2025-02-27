/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:14:09 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/27 16:39:27 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_char_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->mapinfo->map[i])
	{
		while (game->mapinfo->map[i][j])
		{
			if (game->mapinfo->map[i][j] != '0'
				&& game->mapinfo->map[i][j] != '1'
				&& game->mapinfo->map[i][j] != 'N'
				&& game->mapinfo->map[i][j] != 'S'
				&& game->mapinfo->map[i][j] != 'E'
				&& game->mapinfo->map[i][j] != 'W'
				&& !ft_isspace(game->mapinfo->map[i][j])
				&& game->mapinfo->map[i][j] == '\n')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	check_double_pos_start(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = -1;
	while (game->mapinfo->map[i])
	{
		j = 0;
		while (game->mapinfo->map[i][j])
		{
			if (game->mapinfo->map[i][j] == 'N'
				|| game->mapinfo->map[i][j] == 'S'
				|| game->mapinfo->map[i][j] == 'E'
				|| game->mapinfo->map[i][j] == 'W')
			{
				if (flag == 1) 
					return (ft_putstr_fd("Error : Found mutilple start pos\n",2),FALSE);
				flag = 1; 
			}
			j++;
		}
		i++;
	}
	if (flag == -1)
		return (ft_putstr_fd("Error : no start pos in Map\n",2),FALSE);
	return (TRUE);
}