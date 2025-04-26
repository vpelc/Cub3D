/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:37:44 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/26 16:08:43 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_is_dir(char *filename)
{
	int	fd;
	int	ret;

	ret = FALSE;
	fd = open(filename, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		ret = TRUE;
	}
	return (ret);
}

static int	check_extension(char *file_name)
{
	int	i;

	i = ft_strlen(file_name);
	if ((ft_strncmp(file_name + i - 4, EXT_CUB, 4) != 0) | (i <= 4))
		return (FALSE);
	else
		return (TRUE);
}

static int	check_filename(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	close(fd);
	return (TRUE);
}

void	check_args(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		exit_prog("Error: Invalid number of arguments.\n", 1, game);
	if (check_is_dir(argv[1]) == TRUE)
		exit_prog("Error: The given argument is a directory.\n", 1, game);
	if (check_filename(argv[1]) == FALSE)
		exit_prog("Error: File .cub does not exist or cannot be opened.\n", 1,
			game);
	if (check_extension(argv[1]) == FALSE)
		exit_prog("Error: Invalid file extension, expected '.cub'.\n", 1, game);
}
