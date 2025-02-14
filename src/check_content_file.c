/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:52:50 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/14 15:50:05 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

static int check_empty_file(int fd)
{
  char buffer[1];
  
  if (read(fd ,buffer,1) <= 0)
  {
        close(fd);
        return (FALSE);
  }
  close(fd);
  return (TRUE);
}

// static int check_texture(int fd)
// {
//     int check_bool
// }

int check_content_file(char **argv)
{
    int fd;

    fd = open(argv[1],O_RDONLY);
    if (fd == -1)
    {
        close(fd);
        return (FALSE);
    }
    if (check_empty_file(fd) == FALSE)
        return (FALSE);
    if (check_texture(fd) == FALSE)
        return (FALSE);
    return (TRUE);
}