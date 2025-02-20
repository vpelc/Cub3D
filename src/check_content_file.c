/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:52:50 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/20 23:40:36 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_empty_file(int fd)
{
	char	buffer[1];

	if (read(fd, buffer, 1) <= 0)
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

int	check_line_contain_flag(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (FALSE);
	while (ft_isspace(line[i]) == TRUE)
		i++;
	if (line[i] == '\0')
		return (FALSE);
	if (!ft_strncmp(&line[i], "NO", 3) || !ft_strncmp(&line[i], "SO", 3)
		|| !ft_strncmp(&line[i], "WE", 3) || !ft_strncmp(&line[i], "EA", 3))
		return (TRUE);
	if (line[i] == 'F' || line[i] == 'C')
		return (TRUE);
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
	if (!ft_strncmp(flag, "NO", 3) && (game->texinfo->NO_path))
		return (TRUE);
	if (!ft_strncmp(flag, "SO", 3) && (game->texinfo->SO_path))
		return (TRUE);
	if (!ft_strncmp(flag, "WE", 3) && (game->texinfo->WE_path))
		return (TRUE);
	if (!ft_strncmp(flag, "EA", 3) && (game->texinfo->EA_path))
		return (TRUE);
	if (flag[0] == 'F' && game->texinfo->floor)
		return (TRUE);
	if (flag[0] == 'C' && (game->texinfo->ceiling))
		return (TRUE);
	return (FALSE);
}

int	is_valid_rgb_format(char *line)
{
	char	**values;
	int		i;
	int		j;
	int		num;

	i = 0;
	j = 0;
	values = ft_split(line, ',');
	if (!values)
		return (FALSE);
	while (values[i])
		i++;
	if (i != 3)
		return (free_tab(values), FALSE);
	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit(values[i][j]))
			return (free_tab(values), FALSE);
		num = ft_atoi(values[i]);
		if (num < 0 || num > 255)
			return (free_tab(values), FALSE);
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
	if (!is_valid_rgb_format(line + start))
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

int parse_rgb(char *path,int index)
{
	char	**values;
	int 	result;
	
	values = ft_split(path, ',');
	if (!values)
		return (-1);
	result = ft_atoi(values[index]);
	free_tab(values);
	return (result);
}


int fill_color_data(char *flag, char *path, t_game *game)
{
	if (flag[0] == 'F')
	{	
		game->texinfo->floor[0] = parse_rgb(path,0);
		game->texinfo->floor[2] = parse_rgb(path,1);
		game->texinfo->floor[3] = parse_rgb(path,2);
	}
	else if (flag[0] == 'C')
	{
		game->texinfo->ceiling[0] = parse_rgb(path,0);
		game->texinfo->ceiling[1] = parse_rgb(path,1);
		game->texinfo->ceiling[2] = parse_rgb(path,2);
	}	
	else
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
		return (fill_color_data(flag,path,game));
	else
		return (FALSE);
	return (TRUE);
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
		if (line[0] == '\n' || line[0] == '\0')
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
		}
		// else if (check_line_contain_map(line, fd)
		// 	&& (check_texture_is_fill(game) == FALSE))
		// {
		// 	ft_putstr_fd("Error : Missing texture", 2);
		// 	return (FALSE);
		// }
		else
		{
			ft_putstr_fd("Error : invalid data in file", 2);
			return (FALSE);
		}
		free(line);
	}
	free(line);
	return (TRUE);
}

int	check_content_file(t_game *game)
{
	if (check_empty_file(game->mapinfo->fd) == FALSE)
	{
		ft_putstr_fd("Error: File empty\n", 2);
		close(game->mapinfo->fd);
		return (FALSE);
	}
	if (check_texture(game->mapinfo->fd, game) == FALSE)
	{
		close(game->mapinfo->fd);
		return (FALSE);
	}
	close(game->mapinfo->fd);
	return (TRUE);
}