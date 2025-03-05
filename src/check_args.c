/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:15:19 by dbajeux           #+#    #+#             */
/*   Updated: 2025/03/05 16:12:58 by dbajeux          ###   ########.fr       */
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

int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (FALSE);
	}
	if (check_is_dir(argv[1]) == TRUE)
	{
		ft_putstr_fd("Error: The given argument is a directory\n", 2);
		return (FALSE);
	}
	if (check_extension(argv[1]) == FALSE)
	{
		ft_putstr_fd("Error: Invalid file extension, expected '.cub'\n", 2);
		return (FALSE);
	}
	if (check_filename(argv[1]) == FALSE)
	{
		ft_putstr_fd("Error: File does not exist or cannot be opened\n", 2);
		return (FALSE);
	}
	return (TRUE);
}