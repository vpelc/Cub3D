/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:46:49 by dbajeux           #+#    #+#             */
/*   Updated: 2025/04/26 15:10:32 by vpelc            ###   ########.fr       */
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
	unsigned long		hex_floor;
	unsigned long		hex_ceiling;
	int					floor[3];
	int					ceiling[3];
	int					ceilling_check;
	int					floor_check;
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	char				dir;
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
	int					shift_key;
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
	char				**cv_tab;
	int					width;
	int					height;
}						t_map;

typedef struct s_rays
{
	int					mx;
	int					my;
	int					mp;
	int					dof;
	float				r;
	float				hrx;
	float				hry;
	float				vrx;
	float				vry;
	float				rx;
	float				ry;
	float				ra;
	float				xo;
	float				yo;
	float				dray;
	char				dir;
}						t_rays;

typedef struct s_draw
{
	float				ty;
	float				ty_step;
	float				ty_off;
	float				line_h;
	float				line_o;
}						t_draw;

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

// check_args.c
void					check_args(int argc, char **argv, t_game *game);

// check_content_file.c
void					check_content_file(t_game *game, char *filename);

// check_map.c
void					define_size_x_map(t_game *game);
void					check_double_pos_start(t_game *game);
void					check_map_fully_enclosed(t_game *game);

// check_texture_utils.c
int						check_line_contain_map(char *line);
void					check_texture_is_fill(t_game *game);
int						check_doublon_flag(char *flag, t_game *game);
int						check_line_contain_flag(t_game *game, char *line);
int						check_is_empty_line(char *line);

// check_texture_utils2.c
int						check_empty_file(t_game *game, char *filename);
void					check_texture_is_reachable(t_game *game);
int						has_valid_extension(char *path);
int						is_texture_image(char *flag);
int						line_contain_char(char *line);
// check_texture.c
void					parse_line(t_game *game, char *line, int *map_started);

// exit.c
void					free_list(t_game *game);
int						close_window(t_game *game);

// extract_path.c
char					*extract_path(t_game *game, char *line, char *flag);

// fill_data.c
int						fill_texture(char *path, char *flag, t_game *game);

// init.c
void					init_texinfo(t_game *game);
void					init_player(t_game *game);
void					init_texture(t_game *game);
void					init_keys(t_game *game);

// init2.c
int						init_game(t_game *game);

// utils.c
void					free_tab(char **tab);

// utils2.c
int						get_pos_y_player(char **map);
int						get_pos_x_player(char **map);
char					**copy_map(char **map, int height);
int						get_map_width(char **map);
int						convert_map(t_game *game);

// utils3.c
int						ft_isspace(char c);
int						check_tab_empty(int tab[3]);
char					*identify_flag(char *line);
int						is_valid_index(int index);
void					ft_strcpy(char *dst, const char *src);

// utils4.c
int						parse_rgb(char *path, int index);
void					fill_map(char *line, t_game *game);
int						rgb_to_hex(int r, int g, int b);

// display.c

void					create_map_img(t_game *game);
void					draw_map(t_game *game);
void					put_pixel_to_image(t_texture *tex, float x, float y,
							int color);

// display_mini.c

void					create_mini_map_img(t_game *game);
void					draw_mini_map(t_game *game);

// ray_cast.c

void					draw_ray(t_game *game);

// ray_cast_2.c

double					ray_hor(t_game *game, t_rays *ray, double dist_h);
double					ray_ver(t_game *game, t_rays *ray, double dist_v);

// ray_cast_3.c

void					ray_on_line(t_game *game, t_rays *ray, char dir);
void					check_ver_hor(t_rays *ray, double dist_h,
							double dist_v);
void					check_ra(t_rays *ray);
float					dist(float px, float py, float rx, float ry);

// free_utils.c

void					*ft_malloc(t_game *game, size_t size, size_t count);
char					*ft_strdup_list(t_game *game, const char *s1);
char					*ft_substr_list(t_game *game, char const *s,
							unsigned int start, size_t len);
char					*ft_strtrim_list(t_game *game, char const *s1,
							char const *set);

// free_utils_2.c

char					**ft_split_list(t_game *game, char const *str, char c);
void					exit_prog(char *msg, int error, t_game *game);

// texture.c

void					load_win_texture(t_game *game);
void					load_texture(t_game *game, t_image **img, char *name,
							char *path);
void					clear_image(t_texture *tex);
int						get_pixel_color(t_texture *tex, int x, int y);
int						get_pixel_color_r(t_texture *tex, int x, int y);

// movement.c

void					move_up(t_game *game);
void					move_down(t_game *game);
void					move_left(t_game *game);
void					move_right(t_game *game);

// movement_2.c

void					rotate_left(t_game *game);
void					rotate_right(t_game *game);
void					mouse_rotate(t_game *game, int move);

// gnl++

char					*get_next_line_list(int fd, t_game *game);
char					*ft_strjoin_gnl_list(t_game *game, char *buffer,
							char *read_buffer);

#endif