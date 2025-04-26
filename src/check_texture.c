/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:50:07 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/26 18:57:27 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_empty_xpm_file(char *path, t_game *game)
{
	int		fd;
	char	*line_xpm;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_prog("Error: File .xpm does not exist or cannot be opened.\n", 1,
			game);
	line_xpm = get_next_line_dylan(fd);
	close(fd);
	if (!line_xpm)
		return (FALSE);
	if (ft_strncmp(line_xpm, "/* XPM */", 8) == 0)
	{
		free(line_xpm);
		return (TRUE);
	}
	free(line_xpm);
	return (FALSE);
}

static void	check_texture_errors(t_game *game, char *flag, char *path)
{
	if (check_doublon_flag(flag, game) == TRUE)
		exit_prog("Error: Duplicate texture detected.\n", 1, game);
	if (is_texture_image(flag) == TRUE)
	{
		if (check_empty_xpm_file(path, game) == FALSE)
			exit_prog("Error: .xpm file is not valid.\n", 1, game);
		if (!has_valid_extension(path))
			exit_prog("Error: Texture must have .xpm extension.\n", 1, game);
	}
	if (fill_texture(path, flag, game) == FALSE)
		exit_prog("Error: Failed to load texture path.\n", 1, game);
}

void	process_texture_line(t_game *game, char *line)
{
	char	*flag;
	char	*path;

	flag = identify_flag(line);
	if (!flag)
		exit_prog("Error: Missing flag.\n", 1, game);
	path = extract_path(game, line, flag);
	check_texture_errors(game, flag, path);
}

void	handle_map_line(char *line, t_game *game, int *map_started)
{
	if (*map_started == FALSE)
	{
		check_texture_is_fill(game);
		check_texture_is_reachable(game);
		*map_started = TRUE;
	}
	fill_map(line, game);
}

void	parse_line(t_game *game, char *line, int *map_started)
{
	if (check_is_empty_line(line) == TRUE)
	{
		if (*map_started)
		{
			exit_prog("Error: Empty line inside the map.\n", 1, game);
		}
		return ;
	}
	if (*map_started && line_contain_char(line) == TRUE)
		exit_prog("Error: Char not allowed in map.\n", 1, game);
	if (!*map_started && check_line_contain_flag(game, line) == TRUE)
	{
		process_texture_line(game, line);
		return ;
	}
	if (check_line_contain_map(line) == TRUE)
	{
		handle_map_line(line, game, map_started);
		return ;
	}
	exit_prog("Error: Invalid data in .cub file.\n", 1, game);
}
