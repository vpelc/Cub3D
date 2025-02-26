/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:52:50 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/26 23:18:44 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_empty_file(t_game *game, char *filename)
{
	if ((game->mapinfo->fd = open(filename, O_RDONLY)) == -1)
		return (FALSE);
	return (TRUE);
}

int	check_line_contain_flag(char *line)
{
	int		i;
	char	**line_tab;
	char	*trimmed_path;

	i = 0;
	trimmed_path = ft_strtrim((const char *)line, " 	\n");
	line_tab = ft_split(trimmed_path, ' ');
	while (line_tab[i])
		i++;
	if (i != 2)
		return (FALSE);
	if (!ft_strncmp(line_tab[0], "NO", 3) || !ft_strncmp(line_tab[0], "SO", 3)
		|| !ft_strncmp(line_tab[0], "WE", 3) || !ft_strncmp(line_tab[0], "EA",
			3) || !ft_strncmp(line_tab[0], "F", 3) || !ft_strncmp(line_tab[0],
			"C", 3))
	{
		return (TRUE);
	}
	else
		return (FALSE);
}

char	*identify_flag(char *line)
{
	const char	*flags[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (ft_isspace(line[i]) == TRUE)
		i++;
	while (flags[j])
	{
		if (!ft_strncmp(&line[i], flags[j], ft_strlen(flags[j])))
			return ((char *)flags[j]);
		j++;
	}
	return (NULL);
}

int	check_doublon_flag(char *flag, t_game *game)
{
	if (!flag || !game || !game->texinfo)
		return (FALSE);
	if (!ft_strncmp(flag, "NO", 2) && (game->texinfo->NO_path))
		return (TRUE);
	if (!ft_strncmp(flag, "SO", 2) && (game->texinfo->SO_path))
		return (TRUE);
	if (!ft_strncmp(flag, "WE", 2) && (game->texinfo->WE_path))
		return (TRUE);
	if (!ft_strncmp(flag, "EA", 2) && (game->texinfo->EA_path))
		return (TRUE);
	if (flag[0] == 'F' && (game->texinfo->floor) == 0)
		return (TRUE);
	if (flag[0] == 'C' && (game->texinfo->ceiling) == 0)
		return (TRUE);
	return (FALSE);
}

// int	is_valid_rgb_format(char *line)
// {
// 	char	**values;
// 	int		i;
// 	int		j;
// 	int		num;

// 	i = 0;
// 	j = 0;
// 	values = ft_split(line, ',');
// 	if (!values)
// 		return (-1);
// 	while (values[i])
// 		i++;
// 	if (i != 3)
// 		return (free_tab(values), -1);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		j = 0;
// 		while (values[i][j])
// 		{
// 			ft_printf("%c\n",values[i][j]);
// 			if (!ft_isdigit(values[i][j]))
// 				return (free_tab(values), -1);
// 			j++;
// 		}
// 		num = ft_atoi(values[i]);
// 		if (num < 0 || num > 255)
// 			return (free_tab(values), -1);
// 		i++;
// 	}
// 	free_tab(values);
// 	return (TRUE);
// }

int	is_valid_rgb_format(char *line)
{
	char	**values;
	int		i;
	int		j;
	int		num;
	char	*trimmed;

	if (!line || *line == '\0')
		return (-1);
	values = ft_split(line, ',');
	if (!values)
		return (-1);
	i = 0;
	while (values[i])
	{
		trimmed = ft_strtrim(values[i], " ");
		free(values[i]);
		values[i] = trimmed;
		i++;
	}
	if (i != 3)
		return (free_tab(values), -1);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (values[i][j])
		{
			if (values[i][j] == '\n')
			{
				j++;
				continue ;
			}
			if (!ft_isdigit(values[i][j]))
				return (free_tab(values), -1);
			j++;
		}
		num = ft_atoi(values[i]);
		if (num < 0 || num > 255)
			return (free_tab(values), -1);
		i++;
	}
	free_tab(values);
	return (TRUE);
}

char	*extract_colour(char *line)
{
	int	i;
	int	start;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	i += 1;
	while (ft_isspace(line[i]))
		i++;
	start = i;
	if (is_valid_rgb_format(line + start) == -1)
	{
		ft_putstr_fd("Error: Invalid RGB format.\n", 2);
		return (NULL);
	}
	return (ft_strdup(line + start));
}

char	*extract_texture(char *line)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	end = i - 1;
	return (ft_substr(line, start, end - start + 1));
}
char	*extract_path(char *line, char *flag)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]) == TRUE)
		i++;
	if (!ft_strncmp(flag, "NO", 3) || !ft_strncmp(flag, "SO", 3)
		|| !ft_strncmp(flag, "WE", 3) || !ft_strncmp(flag, "EA", 3))
		return (extract_texture(line));
	else if (flag[i] == 'F' || flag[i] == 'C')
		return (extract_colour(line));
	else
		return (NULL);
}

int	parse_rgb(char *path, int index)
{
	char	**values;
	int		result;

	values = ft_split(path, ',');
	if (!values)
		return (-1);
	result = ft_atoi(values[index]);
	free_tab(values);
	return (result);
}

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	fill_hexa(t_game *game)
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

int	fill_color_data(char *flag, char *path, t_game *game)
{
	if (flag[0] == 'F')
	{
		game->texinfo->floor[0] = parse_rgb(path, 0);
		game->texinfo->floor[1] = parse_rgb(path, 1);
		game->texinfo->floor[2] = parse_rgb(path, 2);
	}
	else if (flag[0] == 'C')
	{
		game->texinfo->ceiling[0] = parse_rgb(path, 0);
		game->texinfo->ceiling[1] = parse_rgb(path, 1);
		game->texinfo->ceiling[2] = parse_rgb(path, 2);
	}
	else
		return (FALSE);
	if (fill_hexa(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	fill_data(char *path, char *flag, t_game *game)
{
	if (!ft_strncmp(flag, "NO", 3))
		game->texinfo->NO_path = path;
	else if (!ft_strncmp(flag, "SO", 3))
		game->texinfo->SO_path = path;
	else if (!ft_strncmp(flag, "WE", 3))
		game->texinfo->WE_path = path;
	else if (!ft_strncmp(flag, "EA", 3))
		game->texinfo->EA_path = path;
	else if (flag[0] == 'C' || flag[0] == 'F')
		return (fill_color_data(flag, path, game));
	else
		return (FALSE);
	return (TRUE);
}
int	check_is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n' || line[0] == '\0')
		return (TRUE);
	while (line[i] && ft_isspace(line[i]) == TRUE)
		i++;
	if (line[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

int	check_line_contain_map(char *line)
{
	int	i;

	i = 0;
	if (check_is_empty_line(line) == TRUE || !line)
		return (FALSE);
	while (line[i])
	{
		if (ft_isspace(line[i]) == FALSE && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'S')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_tab_empty(int tab[3])
{
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1)
		return (FALSE);
	return (TRUE);
}
int	check_texture_is_fill(t_game *game)
{
	if (!game || !game->texinfo->NO_path || !game->texinfo->SO_path
		|| !game->texinfo->WE_path || !game->texinfo->EA_path)
		return (FALSE);
	if (check_tab_empty(game->texinfo->floor) == FALSE
		|| check_tab_empty(game->texinfo->ceiling) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	fill_map(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (game->mapinfo->map[i])
		i++;
	game->mapinfo->map[i] = ft_strdup(line);
}

static int	check_texture(int fd, t_game *game)
{
	char	*line;
	char	*path;
	char	*flag;

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
			if (fill_data(path, flag, game) == FALSE)
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

int	count_line_map(int fd)
{
	char	*line;
	int		map_number_line;

	line = NULL;
	map_number_line = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (check_line_contain_map(line) == TRUE)
			map_number_line++;
		free(line);
		continue ;
	}
	close(fd);
	return (map_number_line);
}

// int check_char_map(t_game *game)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;

// 	while (game->mapinfo->map[i]) 
// 	{
// 		while (game->mapinfo->map[i][j])
// 		{
// 			if (game->mapinfo->map[i][j] != '0' || game->mapinfo->map[i][j] != '1' || game->mapinfo->map[i][j] != 'N' || game->mapinfo->map[i][j] != 'S' || game->mapinfo->map[i][j] != 'E' || game->mapinfo->map[i][j] != 'W')  )
// 			j++;
// 		}
// 		i++;
// 	}
// }

// int check_validity_map(t_game *game)
// {
// 	if (check_char_map (game) == FALSE)
// 		return (ft_putstr_fd("Invalid Char in Map", 2),FALSE);
// }
int	check_content_file(t_game *game, char *filename)
{
	if (check_empty_file(game, filename) == FALSE)
	{
		ft_putstr_fd("Error: File empty\n", 2);
		return (FALSE);
	}
	game->mapinfo->map_number_line = count_line_map(game->mapinfo->fd);
	game->mapinfo->fd = open(filename, O_RDONLY);
	game->mapinfo->map = malloc((sizeof(char *)
				* game->mapinfo->map_number_line) + 1);
	if (check_texture(game->mapinfo->fd, game) == FALSE)
	{
		close(game->mapinfo->fd);
		return (FALSE);
	}
	// if (check_validity_map(game) == FALSE)
	// 	return(ft_putstr_fd("Map Invalid", 2),FALSE);
	close(game->mapinfo->fd);
	return (TRUE);
}