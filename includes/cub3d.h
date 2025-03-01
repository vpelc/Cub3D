/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:46:49 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/27 18:16:46 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                 INCLUDE                                    */
/* ************************************************************************** */

# include "libft/inc/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <stdio.h>

/* ************************************************************************** */
/*                                 MACRO                                      */
/* ************************************************************************** */

# define TRUE 0
# define FALSE 1
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

typedef struct s_game
{
	void				*mlx;
	void				*win;
	struct s_free		*to_free;
	struct s_keys		*keys;
	struct s_map		*map;
	struct s_player		*player;
	struct s_texture	*win_img;
	void				*p_img;
	void				*w_img;
	void				*e_img;
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
	t_game				*game;
}						t_player;

typedef struct s_map
{
	char				**tab;
	int					*width;
	int					*heigth;
	t_game				*game;
}						t_map;

typedef struct s_rays
{
	float				r;
	int					mx;
	int					my;
	int					mp;
	int					dof;
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

// typedef struct s_image
// {
// 	void			*image;
// 	int				width;
// 	int				height;
// }					t_image;

typedef struct s_free
{
	void				*content;
	struct s_free		*next;
}						t_free;

/* ************************************************************************** */
/*                                 FUNCTION                                   */
/* ************************************************************************** */

void					*ft_malloc(t_game *game, size_t size, size_t count);
int						close_window(t_game *game);
int						init_game(t_game *game);
void					draw_map(t_game *game);
void					draw_player(t_game *game);
void					draw_ray(t_game *game);
void					put_pixel_to_image(t_texture *tex, float x, float y,
							int color);
void					load_win_texture(t_game *game);
void					clear_image(t_texture *tex);
void					move_up(t_game *game);
void					move_down(t_game *game);
void					move_left(t_game *game);
void					move_right(t_game *game);
void					rotate_left(t_game *game);
void					rotate_right(t_game *game);

#endif