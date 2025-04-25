/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:33:06 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/25 12:32:41 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int	is_file_xpm(t_game *game)
// {
// 	if (!game->texinfo->no_path || !ft_strnstr(game->texinfo->no_path, EXT_XPM,
// 			ft_strlen(game->texinfo->no_path)))
// 		return (FALSE);
// 	if (!game->texinfo->so_path || !ft_strnstr(game->texinfo->so_path, EXT_XPM,
// 			ft_strlen(game->texinfo->so_path)))
// 		return (FALSE);
// 	if (!game->texinfo->we_path || !ft_strnstr(game->texinfo->we_path, EXT_XPM,
// 			ft_strlen(game->texinfo->we_path)))
// 		return (FALSE);
// 	if (!game->texinfo->ea_path || !ft_strnstr(game->texinfo->ea_path, EXT_XPM,
// 			ft_strlen(game->texinfo->ea_path)))
// 		return (FALSE);
// 	return (TRUE);
// }

int	check_empty_file(t_game *game, char *filename)
{
	char	*line;

	game->map->fd = open(filename, O_RDONLY);
	line = get_next_line(game->map->fd);
	close(game->map->fd);
	if (line == NULL)
		return (FALSE);
	free(line);
	return (TRUE);
}

void	check_texture_is_reachable(t_game *game)
{
	int	fd_no;
	int	fd_so;
	int	fd_we;
	int	fd_ea;

	fd_no = open(game->texinfo->no_path, O_RDONLY);
	fd_so = open(game->texinfo->so_path, O_RDONLY);
	fd_we = open(game->texinfo->we_path, O_RDONLY);
	fd_ea = open(game->texinfo->ea_path, O_RDONLY);
	if (fd_no == -1 || fd_so == -1 || fd_we == -1 || fd_ea == -1)
		exit_prog("Error : texture/image not reachable.\n", 2, game);
	close(fd_no);
	close(fd_so);
	close(fd_we);
	close(fd_ea);
}

int	has_valid_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	return (len > 4 && ft_strncmp(path + len - 4, ".xpm",
			ft_strlen(path)) == 0);
}

int	is_texture_image(char *flag)
{
	if (!ft_strncmp("NO", flag, ft_strlen(flag)) || !ft_strncmp("SO", flag,
			ft_strlen(flag)) || !ft_strncmp("WE", flag, ft_strlen(flag))
		|| !ft_strncmp("EA", flag, ft_strlen(flag)))
		return (TRUE);
	return (FALSE);
}

int	line_contain_char(char *line)
{
	int		i;
	char	current_char;

	i = 0;
	while (line[i])
	{
		current_char = line[i];
		if (current_char != '0' && current_char != '1' && current_char != 'N'
			&& current_char != 'S' && current_char != 'E' && current_char != 'W'
			&& ft_isspace(current_char) == FALSE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
