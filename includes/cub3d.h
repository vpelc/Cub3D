/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:46:49 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/17 14:04:41 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_h

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

# define ZOOM 1
# define SQR_SIZE 63
# define P_SIZE 8

/* ************************************************************************** */
/*                                 STRUCT                                     */
/* ************************************************************************** */

typedef struct s_game
{
	void			*mlx;
	void			*win;
	struct s_free	*to_free;
	struct s_keys	*keys;
	struct s_map	*map;
	struct s_player	*player;
	void			*p_img;
	void			*w_img;
	void			*e_img;
}					t_game;

typedef struct s_keys
{
	int				left_key;
	int				right_key;
	int				up_key;
	int				down_key;
}					t_keys;

typedef struct s_player
{
	float			posx;
	float			posy;
	float			posdx;
	float			posdy;
	float			posa;
	t_game			*game;
}					t_player;

typedef struct s_map
{
	char			**tab;
	t_game			*game;
}					t_map;

typedef struct s_rays
{
	int				r;
	int				mx;
	int				my;
	int				mp;
	int				dof;
	float			rx;
	float			ry;
	float			ra;
	float			xo;
	float			yo;
}					t_rays;

// typedef struct s_image
// {
// 	void			*image;
// 	int				width;
// 	int				height;
// }					t_image;

typedef struct s_free
{
	void			*content;
	struct s_free	*next;
}					t_free;

/* ************************************************************************** */
/*                                 FUNCTION                                   */
/* ************************************************************************** */

void				*ft_malloc(t_game *game, size_t size, size_t count);
int					close_window(t_game *game);
int					init_game(t_game *game);
void				draw_map(t_game *game);
void				draw_player(t_game *game);
float				draw_rays_h(t_game *game);
float				draw_rays_v(t_game *game);
void				draw_ray_lines(t_game *game, float dray, char c);

#endif