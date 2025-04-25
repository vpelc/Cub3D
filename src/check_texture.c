/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:50:07 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/25 12:52:30 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_invalid_map_char(char *line, t_game *game)
{
	free(line);
	exit_prog("Error: Char not allowed in map.\n", 1, game);
}

void	process_texture_line(t_game *game, char *line)
{
	char	*flag;
	char	*path;

	flag = identify_flag(line);
	if (!flag)
		free(line);
	if (check_doublon_flag(flag, game) == TRUE)
	{
		free(line);
		exit_prog("Error: Duplicate texture detected.\n", 1, game);
	}
	path = extract_path(game, line, flag);
	if (!has_valid_extension(path) && is_texture_image(flag) == TRUE)
	{
		free(line);
		exit_prog("Error: Texture must have .xpm extension.\n", 1, game);
	}
	if (fill_texture(path, flag, game, line) == FALSE)
	{
		free(line);
		exit_prog("Error: Failed to load texture path.\n", 1, game);
	}
	free(line);
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
	free(line);
}

void	parse_line(t_game *game, char *line, int *map_started)
{
	if (check_is_empty_line(line) == TRUE)
	{
		if (*map_started)
		{
			free(line);
			exit_prog("Error: Empty line inside the map.\n", 1, game);
		}
		free(line);
		return ;
	}
	if (*map_started && line_contain_char(line) == TRUE)
		exit_invalid_map_char(line, game);
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
	free(line);
	exit_prog("Error: Invalid data in .cub file.\n", 1, game);
}
