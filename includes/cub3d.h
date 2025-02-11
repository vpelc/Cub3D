/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:46:49 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/11 14:03:59 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_h

/* ************************************************************************** */
/*                                 INCLUDE                                    */
/* ************************************************************************** */

# include "libft/inc/libft.h"
# include "minilibx/mlx.h"

/* ************************************************************************** */
/*                                 MACRO                                      */
/* ************************************************************************** */

# define TRUE 0
# define FALSE 1

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
	int				posx;
	int				posy;
	t_game			*game;
}					t_player;

typedef struct s_map
{
	char			**tab;
	t_game			*game;
}					t_map;

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

#endif