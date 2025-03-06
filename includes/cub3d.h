/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:46:49 by dbajeux           #+#    #+#             */
/*   Updated: 2025/03/06 16:54:43 by vpelc            ###   ########.fr       */
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
# include <math.h>
# include <stdio.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                 MACRO                                      */
/* ************************************************************************** */

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif
# define FALSE 0
# define TRUE 1
# define EXT_CUB ".cub"
# define EXT_XPM ".xpm"
# define PI 3.1415926535
# define EPSILON 1e-6
# define RAD_DEG 0.0174532925

# define SCR_WIDTH 1000
# define SCR_HEIGHT 1000
# define SQR_SIZE 64
# define P_SIZE 8

/* ************************************************************************** */
/*                                 STRUCT                                     */
/* ************************************************************************** */

typedef struct s_texinfo
{
	char				*NO_path;
	char				*SO_path;
	char				*WE_path;
	char				*EA_path;
	int					floor[3];
	int					ceiling[3];
	unsigned long		hex_floor;
	unsigned long		hex_ceiling;
}						t_texinfo;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	struct s_free		*to_free;
	struct s_keys		*keys;
	struct s_map		*map;
	struct s_player		*player;
	struct s_texture	*win_img;
	struct s_texture	*map_img;
	struct s_texture	*minimap_img;
	struct s_image		*img_no;
	struct s_image		*img_so;
	struct s_image		*img_we;
	struct s_image		*img_ea;
	t_texinfo			*texinfo;
}						t_game;

typedef struct s_keys
{
	int					left_key;
	int					right_key;
	int					up_key;
	int					down_key;
	int					rotl_key;
	int					rotr_key;
}						t_keys;

typedef struct s_player
{
	float				posx;
	float				posy;
	float				posdx;
	float				posdy;
	float				posdxp;
	float				posdyp;
	float				posa;
}						t_player;

typedef struct s_map
{
	int					fd;
	char				**tab;
	int					width;
	int					height;
}						t_map;

typedef struct s_rays
{
	float				r;
	int					mx;
	int					my;
	int					mp;
	int					dof;
	float				hrx;
	float				hry;
	float				vrx;
	float				vry;
	float				rx;
	float				ry;
	float				ra;
	float				xo;
	float				yo;
}						t_rays;
typedef struct s_texture
{
	void				*img;
	char				*addr;
	int					width;
	int					height;
	int					bpp;
	int					size_line;
	int					endian;
}						t_texture;

typedef struct s_image
{
	char				*name;
	t_texture			*texture;
}						t_image;

typedef struct s_free
{
	void				*content;
	struct s_free		*next;
}						t_free;

/* ************************************************************************** */
/*                                 FUNCTION                                   */
/* ************************************************************************** */

// check_args
int						check_args(int argc, char **argv);

// check content file
int						check_content_file(t_game *game, char *filename);

// check map
int						check_double_pos_start(t_game *game);
int						check_char_map(t_game *game);
int						check_map_fully_enclosed(t_game *game);

// check texture
int						check_line_contain_map(char *line);
int						check_texture_is_fill(t_game *game);
int						check_doublon_flag(char *flag, t_game *game);
int						check_line_contain_flag(char *line);
int						check_is_empty_line(char *line);

// extract path
char					*extract_path(char *line, char *flag);

// fill data
void					fill_map(char *line, t_game *game);
int						fill_texture(char *path, char *flag, t_game *game);

// init
void					init_data(t_game *game);

// utils
int						ft_isspace(char c);
void					free_tab(char **tab);
int						count_line_map(int fd);
int						check_tab_empty(int tab[3]);
char					*identify_flag(char *line);
int						rgb_to_hex(int r, int g, int b);
int						get_pos_y_player(char **map);
int						get_pos_x_player(char **map);
char					**copy_map(char **map, int height);
int						get_map_width(char **map);

// print !!only test!!
void					print_game(t_game *game);
void					print_mapinfo(t_mapinfo *mapinfo);
void					print_texinfo(t_texinfo *texinfo);
void					print_map(char **map);
void					*ft_malloc(t_game *game, size_t size, size_t count);
int						close_window(t_game *game);
int						init_game(t_game *game);
void					draw_map(t_game *game);
void					draw_player(t_game *game);
void					draw_ray(t_game *game);
void					put_pixel_to_image(t_texture *tex, float x, float y,
							int color);
void					load_win_texture(t_game *game);
void					load_texture(t_game *game, t_image **img, char *name,
							char *path);
void					clear_image(t_texture *tex);
void					move_up(t_game *game);
void					move_down(t_game *game);
void					move_left(t_game *game);
void					move_right(t_game *game);
void					rotate_left(t_game *game);
void					rotate_right(t_game *game);
int						get_pixel_color(t_texture *tex, int x, int y);
int						get_pixel_color_r(t_texture *tex, int x, int y);
void					create_map_img(t_game *game);
void					create_mini_map_img(t_game *game);
void					draw_mini_map(t_game *game);
void					mouse_rotate(t_game *game, int move);

#endif