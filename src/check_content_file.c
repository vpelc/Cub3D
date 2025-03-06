/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:52:50 by dbajeux           #+#    #+#             */
/*   Updated: 2025/03/06 15:19:09 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_empty_file(t_game *game, char *filename)
{
	char	*line;

	game->mapinfo->fd = open(filename, O_RDONLY);
	line = get_next_line(game->mapinfo->fd);
	close(game->mapinfo->fd);
	if (line == NULL)
		return (FALSE);
	return (TRUE);
}

static int	check_texture(t_game *game, char *filename)
{
	char	*line;
	char	*path;
	char	*flag;
	int		fd;

	fd = open(filename, O_RDONLY);
	path = NULL;
	flag = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (check_is_empty_line(line) == TRUE)
		{
			free(line);
			continue ;
		}
		if (check_line_contain_flag(line) == TRUE)
		{
			flag = identify_flag(line);
			if (!flag)
				return (FALSE);
			if (check_doublon_flag(flag, game) == TRUE)
			{
				free(line);
				ft_putstr_fd("Error: Duplicate texture detected.\n", 2);
				return (FALSE);
			}
			path = extract_path(line, flag);
			if (fill_texture(path, flag, game) == FALSE)
			{
				free(line);
				return (FALSE);
			}
			continue ;
		}
		if ((check_texture_is_fill(game) == TRUE)
			&& (check_line_contain_map(line) == TRUE))
		{
			fill_map(line, game);
			continue ;
		}
		else
		{
			ft_putstr_fd("Error : invalid data in file", 2);
			free(line);
			return (FALSE);
		}
		free(line);
	}
	free(line);
	return (TRUE);
}

static int	check_validity_map(t_game *game)
{
	if (check_char_map(game) == FALSE)
		return (ft_putstr_fd("Invalid Char in Map\n", 2), FALSE);
	if (check_double_pos_start(game) == FALSE)
		return (FALSE);
	if (check_map_fully_enclosed(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	init_map(t_game *game, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		game->mapinfo->map[i] = NULL;
		i++;
	}
}

int	check_content_file(t_game *game, char *filename)
{
	if (check_empty_file(game, filename) == FALSE)
	{
		ft_putstr_fd("Error: File empty\n", 2);
		return (FALSE);
	}
	game->mapinfo->fd = open(filename, O_RDONLY);
	game->mapinfo->map_number_line = count_line_map(game->mapinfo->fd);
	close(game->mapinfo->fd);
	game->mapinfo->map = malloc((sizeof(char *)
				* (game->mapinfo->map_number_line + 1)));
	if (!game->mapinfo->map)
		return (ft_putstr_fd("Error :malloc map", 2), FALSE);
	init_map(game, game->mapinfo->map_number_line);
	if (check_texture(game, filename) == FALSE)
		return (FALSE);
	if (check_validity_map(game) == FALSE)
		return (ft_putstr_fd("Map Invalid\n", 2), FALSE);
	return (TRUE);
}
