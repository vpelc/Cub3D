/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:38:04 by vpelc             #+#    #+#             */
/*   Updated: 2025/04/16 15:14:46 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (TRUE);
	else
		return (FALSE);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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

int	check_tab_empty(int tab[3])
{
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1)
		return (FALSE);
	return (TRUE);
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


void	free_list(t_game *game)
{
	t_free	*tmp;
	t_free	*list;

	list = game->to_free;
	while (list != NULL)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}

void	free_img(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img_ea->texture->img);
	mlx_destroy_image(game->mlx, game->img_no->texture->img);
	mlx_destroy_image(game->mlx, game->img_so->texture->img);
	mlx_destroy_image(game->mlx, game->img_we->texture->img);
	mlx_destroy_image(game->mlx, game->win_img->img);
	mlx_destroy_image(game->mlx, game->map_img->img);
	mlx_destroy_image(game->mlx, game->minimap_img->img);
}

int	close_window(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	free_img(game);
	mlx_destroy_window(game->mlx, game->win);
	free_list(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return 1;
}
