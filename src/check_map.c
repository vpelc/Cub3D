/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:14:09 by dbajeux           #+#    #+#             */
/*   Updated: 2025/03/11 15:35:12 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	convert_map(t_game *game)
{
	char	**cv_map;
	int		i;
	
	cv_map = malloc(sizeof(char *) * (game->map->height + 1));
	if (!cv_map)
		return (FALSE);
	i = 0;
	while (i < game->map->height)
	{
		cv_map[i] = malloc(sizeof(char) * (game->map->width + 1));
		if (!cv_map[i])
			return (FALSE);
		ft_memset(cv_map[i], ' ', game->map->width);
		cv_map[i][game->map->width] = '\0';
		ft_strcpy(cv_map[i], game->map->tab[i]);
		i++;
	}
	game->map->cv_tab = cv_map;
	return (TRUE);
}

int	check_char_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->tab[i])
	{
		j = 0;
		while (game->map->tab[i][j])
		{
			if (game->map->tab[i][j] != '0'
				&& game->map->tab[i][j] != '1'
				&& game->map->tab[i][j] != 'N'
				&& game->map->tab[i][j] != 'S'
				&& game->map->tab[i][j] != 'E'
				&& game->map->tab[i][j] != 'W'
				&& !ft_isspace(game->map->tab[i][j]))
				return (FALSE);
			j++;
		}
		if (game->map->width < j)
			game->map->width = j;
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
	while (game->map->tab[i])
	{
		j = 0;
		while (game->map->tab[i][j])
		{
			if (game->map->tab[i][j] == 'N'
				|| game->map->tab[i][j] == 'S'
				|| game->map->tab[i][j] == 'E'
				|| game->map->tab[i][j] == 'W')
			{
				if (flag == 1)
					return (ft_putstr_fd("Error : Found mutilple start pos\n",
							2), FALSE);
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (flag == -1)
		return (ft_putstr_fd("Error : no start pos in Map\n", 2), FALSE);
	return (TRUE);
}

void	fill_flood(char **map, int y, int x, int *flag, t_game *game)
{
	if (y < 0 || y >= game->map->height || x < 0
		|| x >= (int)ft_strlen(map[y]))
		return ;
	if (*flag == 1 && map[y][x] == ' ')
		*flag = 0;
	if (*flag == 1 && map[y][x] == '0' && (y == 0
			|| y == game->map->height - 1 || x == 0
			|| x == (int)ft_strlen(map[y]) - 1))
		*flag = 0;
	map[y][x] = 'F';
	if (y + 1 < game->map->height && (int)ft_strlen(map[y + 1]) > x
		&& map[y + 1][x] != 'F' && map[y + 1][x] != '1')
		fill_flood(map, y + 1, x, flag, game);
	if (y > 0 && (int)ft_strlen(map[y - 1]) > x && map[y - 1][x] != 'F' && map[y
		- 1][x] != '1')
		fill_flood(map, y - 1, x, flag, game);
	if (x + 1 < (int)ft_strlen(map[y]) && map[y][x + 1] != 'F' && map[y][x
		+ 1] != '1')
		fill_flood(map, y, x + 1, flag, game);
	if (x > 0 && map[y][x - 1] != 'F' && map[y][x - 1] != '1')
		fill_flood(map, y, x - 1, flag, game);
}

int	check_map_fully_enclosed(t_game *game)
{
	char	**map_copy;
	int		flag;
	int		start_y;
	int		start_x;

	map_copy = copy_map(game->map->tab, game->map->height);
	flag = 1;
	if (!map_copy)
		return (ft_putstr_fd("Error : malloc copy map\n", 2), FALSE);
	start_y = get_pos_y_player(map_copy);
	start_x = get_pos_x_player(map_copy);
	game->player->posy = (start_y * 64) + 32;
	game->player->posx = (start_x * 64) + 32;
	fill_flood(map_copy, start_y, start_x, &flag, game);
	if (flag == 0)
	{
		free_tab(map_copy);
		return (ft_putstr_fd("Error map not fully enclosed\n", 2), FALSE);
	}
	game->texinfo->dir = game->map->tab[start_y][start_x];
	game->map->tab[start_y][start_x] = '0';
	free_tab(map_copy);
	return (TRUE);
}
