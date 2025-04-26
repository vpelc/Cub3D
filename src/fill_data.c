/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:20:15 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/26 15:10:03 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	fill_hexa(t_game *game)
{
	game->texinfo->hex_floor = rgb_to_hex(game->texinfo->floor[0],
			game->texinfo->floor[1], game->texinfo->floor[2]);
	game->texinfo->hex_ceiling = rgb_to_hex(game->texinfo->ceiling[0],
			game->texinfo->ceiling[1], game->texinfo->ceiling[2]);
	if (game->texinfo->hex_ceiling == 0x0 || game->texinfo->hex_floor == 0x0)
		return (FALSE);
	else
		return (TRUE);
}

static void	set_floor_rgb(char *path, t_game *game)
{
	game->texinfo->floor[0] = parse_rgb(path, 0);
	game->texinfo->floor[1] = parse_rgb(path, 1);
	game->texinfo->floor[2] = parse_rgb(path, 2);
	game->texinfo->floor_check = TRUE;
	if (game->texinfo->floor[0] == -1 || game->texinfo->floor[1] == -1
		|| game->texinfo->floor[2] == -1)
	{
		exit_prog("Error: Missing RGB value floor.\n", 1, game);
	}
}

static void	set_ceiling_rgb(char *path, t_game *game)
{
	game->texinfo->ceiling[0] = parse_rgb(path, 0);
	game->texinfo->ceiling[1] = parse_rgb(path, 1);
	game->texinfo->ceiling[2] = parse_rgb(path, 2);
	game->texinfo->ceilling_check = TRUE;
	if (game->texinfo->ceiling[0] == -1 || game->texinfo->ceiling[1] == -1
		|| game->texinfo->ceiling[2] == -1)
	{
		exit_prog("Error: Missing RGB value ceiling.\n", 1, game);
	}
}

static int	fill_color_data(char *flag, char *path, t_game *game)
{
	if (flag[0] == 'F')
		set_floor_rgb(path, game);
	else if (flag[0] == 'C')
		set_ceiling_rgb(path, game);
	else
		return (FALSE);
	if (fill_hexa(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	fill_texture(char *path, char *flag, t_game *game)
{
	if (!ft_strncmp(flag, "NO", 3))
		game->texinfo->no_path = path;
	else if (!ft_strncmp(flag, "SO", 3))
		game->texinfo->so_path = path;
	else if (!ft_strncmp(flag, "WE", 3))
		game->texinfo->we_path = path;
	else if (!ft_strncmp(flag, "EA", 3))
		game->texinfo->ea_path = path;
	else if (flag[0] == 'C' || flag[0] == 'F')
		return (fill_color_data(flag, path, game));
	else
	{
		return (FALSE);
	}
	return (TRUE);
}
