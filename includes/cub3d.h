/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:46:49 by dbajeux           #+#    #+#             */
/*   Updated: 2025/03/06 15:26:34 by dbajeux          ###   ########.fr       */
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

// check_args
int					check_args(int argc, char **argv);

// check content file
int					check_content_file(t_game *game, char *filename);

// check map
int					check_double_pos_start(t_game *game);
int					check_char_map(t_game *game);
int					check_map_fully_enclosed(t_game *game);

// check texture
int					check_line_contain_map(char *line);
int					check_texture_is_fill(t_game *game);
int					check_doublon_flag(char *flag, t_game *game);
int					check_line_contain_flag(char *line);
int					check_is_empty_line(char *line);

// extract path
char				*extract_path(char *line, char *flag);

// fill data
void				fill_map(char *line, t_game *game);
int					fill_texture(char *path, char *flag, t_game *game);

// init
void				init_data(t_game *game);

// utils
int					ft_isspace(char c);
void				free_tab(char **tab);
int					count_line_map(int fd);
int					check_tab_empty(int tab[3]);
char				*identify_flag(char *line);
int					rgb_to_hex(int r, int g, int b);
int					get_pos_y_player(char **map);
int					get_pos_x_player(char **map);
char				**copy_map(char **map, int height);
int					get_map_width(char **map);

// print !!only test!!
void				print_game(t_game *game);
void				print_mapinfo(t_mapinfo *mapinfo);
void				print_texinfo(t_texinfo *texinfo);
void				print_map(char **map);

#endif