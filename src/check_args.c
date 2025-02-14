/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:15:19 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/14 14:48:25 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_is_dir(char *filename)
{
    int fd;
    int ret;
    
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

	i = 0;
	while (file_name[i])
		i++;
	if (ft_strncmp(file_name + i - 4, EXT, 4) != 0)
		return (FALSE);
	else
		return (TRUE);
}

static int	check_filename(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
        close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

int	check_args(int argc, char **argv)
{
	if (argc != 2)
		return (FALSE);
	if (check_is_dir(argv[1]) == TRUE)
		return (FALSE);
	if (check_extension(argv[1]) == FALSE)
		return (FALSE);
	if (check_filename(argv[1]) == FALSE)
		return (FALSE);
	return (TRUE);
}