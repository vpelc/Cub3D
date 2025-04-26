/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:52:50 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/26 14:04:36 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_line_map(int fd)
{
	char	*line;
	int		map_number_line;

	line = get_next_line(fd);
	map_number_line = 0;
	while (line != NULL)
	{
		if (check_line_contain_map(line) == TRUE)
			map_number_line++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_number_line);
}

static void	check_texture(t_game *game, char *filename)
{
	char	*line;
	int		fd;
	int		map_started;

	fd = open(filename, O_RDONLY);
	map_started = FALSE;
	if (fd < 0)
		exit_prog("Error: Failed to open file.\n", 1, game);
	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_line(game, line, &map_started);
		line = get_next_line(fd);
	}
	close(fd);
	if (map_started == FALSE)
		exit_prog("Error: No map in .cub file.\n", 1, game);
}

static void	check_validity_map(t_game *game)
{
	define_size_x_map(game);
	check_double_pos_start(game);
	check_map_fully_enclosed(game);
}

static void	init_map(t_game *game, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		game->map->tab[i] = NULL;
		i++;
	}
}

void	check_content_file(t_game *game, char *filename)
{
	if (check_empty_file(game, filename) == FALSE)
		exit_prog("Error: File .cub is empty.\n", 1, game);
	game->map->fd = open(filename, O_RDONLY);
	game->map->height = count_line_map(game->map->fd);
	close(game->map->fd);
	game->map->tab = ft_malloc(game, (sizeof(char *)), (game->map->height + 1));
	if (!game->map->tab)
		return (exit_prog("Error : malloc map", 1, game));
	init_map(game, game->map->height);
	check_texture(game, filename);
	check_validity_map(game);
	close(game->map->fd);
}
