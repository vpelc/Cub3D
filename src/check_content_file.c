/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:52:50 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/23 16:23:24 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_empty_file(t_game *game, char *filename)
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

int	is_file_xpm(t_game *game)
{
	if (!game->texinfo->NO_path || !ft_strnstr(game->texinfo->NO_path, EXT_XPM, ft_strlen(game->texinfo->NO_path)))
		return (FALSE);
	if (!game->texinfo->SO_path || !ft_strnstr(game->texinfo->SO_path, EXT_XPM, ft_strlen(game->texinfo->SO_path)))
		return (FALSE);
	if (!game->texinfo->WE_path || !ft_strnstr(game->texinfo->WE_path, EXT_XPM, ft_strlen(game->texinfo->WE_path)))
		return (FALSE);
	if (!game->texinfo->EA_path || !ft_strnstr(game->texinfo->EA_path, EXT_XPM, ft_strlen(game->texinfo->EA_path)))
		return (FALSE);
	return (TRUE);
}

static void check_texture_is_reachable(t_game *game)
{
	int fd_NO;
	int fd_SO;
	int fd_WE;
	int fd_EA;

	fd_NO = open (game->texinfo->NO_path,O_RDONLY);
	fd_SO = open (game->texinfo->SO_path,O_RDONLY);
	fd_WE = open (game->texinfo->WE_path,O_RDONLY);
	fd_EA = open (game->texinfo->EA_path,O_RDONLY);
	if (fd_NO == -1 || fd_SO == -1 || fd_WE == -1 || fd_EA == -1)
		exit_prog("Error : texture/image not reachable.\n",2,game);
	close(fd_NO);
	close(fd_SO);
	close(fd_WE);
	close(fd_EA);
}

int has_valid_extension(char *path)
{
    int len ;
	len = ft_strlen(path);
    return (len > 4 && ft_strncmp(path + len - 4, ".xpm",ft_strlen(path)) == 0);
}

int is_texture_image(char *flag)
{
	if (!ft_strncmp("NO",flag,ft_strlen(flag)) || !ft_strncmp("SO",flag,ft_strlen(flag)) 
	|| !ft_strncmp("WE",flag,ft_strlen(flag)) || !ft_strncmp("EA",flag,ft_strlen(flag)))
		return (TRUE);
	return (FALSE);
}
int line_contain_char(char *line)
{
	int i;
    char current_char;
    
	i = 0;  
    while (line[i]) 
    {
        current_char = line[i];  
        if (current_char != '0' &&
            current_char != '1' &&
            current_char != 'N' &&
            current_char != 'S' &&
            current_char != 'E' &&
            current_char != 'W' &&
            ft_isspace(current_char) == FALSE)
            return (TRUE);
        i++;
    }
    return (FALSE);
}
static void	check_texture(t_game *game, char *filename)
{
	char	*line;
	char	*path;
	char	*flag;
	int		fd;
	int		map_started = FALSE;

	
	fd = open(filename, O_RDONLY);
	path = NULL;
	flag = NULL;
	map_started =  FALSE;
	if (fd < 0)
		exit_prog("Error: Failed to open file.\n",1,game);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (check_is_empty_line(line) == TRUE)
		{
			if (map_started)
			{
				free(line);
				exit_prog("Error: Empty line inside the map.\n",1,game);
			}
			free(line);
			continue ;
		}
		if (map_started == TRUE)
		{
		 	if (line_contain_char(line) == TRUE)
		 	{
		 		free(line);
		 		exit_prog("Error: Char not allowed in map.\n", 1, game);
		 	}
		}
		if (map_started == FALSE && check_line_contain_flag(game, line) == TRUE)
		{
			flag = identify_flag(line);
			if (!flag)
				free(line);
			if (check_doublon_flag(flag, game) == TRUE)
			{
				free(line);
				exit_prog("Error: Duplicate texture detected.\n", 1,game);
			}
			path = extract_path(game, line, flag);
			if (!has_valid_extension(path) && is_texture_image(flag) == TRUE)
			{
				free(line);
                exit_prog("Error: Texture must have .xpm extension.\n", 1, game);
			}
			if (fill_texture(path, flag, game,line) == FALSE)
			{
				free(line);
				exit_prog("Error: Failed to load texture path.\n",1,game);
			}
			free(line);
			continue ;
		}
		if ((check_line_contain_map(line) == TRUE))
		{
			if(map_started == FALSE)
			{
				check_texture_is_fill(game);
				check_texture_is_reachable(game);
				map_started = TRUE;
			}
			fill_map(line, game);
			free(line);
			continue ;
		}
		free(line);
		exit_prog("Error: Invalid data in .cub file.\n", 1, game);
	}
	close(fd);
	if(map_started == FALSE)
	{
		
		exit_prog("Error: No map in .cub file.\n",1,game);
	}
	free(line);
}

static void	check_validity_map(t_game *game)
{
	define_size_x_map(game);
	check_double_pos_start(game);
	check_map_fully_enclosed(game);
}

void	init_map(t_game *game, int height)
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
		exit_prog("Error: File empty.\n", 1,game);
	game->map->fd = open(filename, O_RDONLY);
	game->map->height = count_line_map(game->map->fd);
	close(game->map->fd);
	game->map->tab = ft_malloc(game, (sizeof(char *)), (game->map->height + 1));
	if (!game->map->tab)
		return (exit_prog("Error : malloc map", 1,game));
	init_map(game, game->map->height);
	check_texture(game, filename);
	check_validity_map(game);
	close(game->map->fd);
}
