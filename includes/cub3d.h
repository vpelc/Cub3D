/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:46:49 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/24 22:31:16 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                 INCLUDE                                    */
/* ************************************************************************** */

# include "libft/inc/libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                 MACCRO                                     */
/* ************************************************************************** */

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif
# define FALSE 0
# define TRUE 1
# define EXT_CUB ".cub"
# define EXT_XPM ".xpm"

/* ************************************************************************** */
/*                                 STRUCT                                     */
/* ************************************************************************** */

typedef struct s_texinfo
{
	char			*NO_path;
	char			*SO_path;
	char			*WE_path;
	char			*EA_path;
	int				floor[3];
	int				ceiling[3];
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
}					t_texinfo;
typedef struct s_mapinfo
{
	int				fd;
	char			**map;
	int				map_number_line;
}					t_mapinfo;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_mapinfo		*mapinfo;
	t_texinfo		*texinfo;
}					t_game;

/* ************************************************************************** */
/*                                 FUNCTION                                   */
/* ************************************************************************** */

int					check_args(int argc, char **argv);
int					check_content_file(t_game *game, char *filename);
void				init_data(t_game *game);
int					get_max_line_infile(int fd);
int					ft_isspace(char c);
void				free_tab(char **tab);
void				print_game(t_game *game);
#endif