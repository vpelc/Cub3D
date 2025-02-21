/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:37:32 by vpelc             #+#    #+#             */
/*   Updated: 2025/02/20 15:47:25 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_texture(t_game *game)
{
	t_texture	tex;

	tex.width = 32;
	tex.height = 32;
	tex.bpp = 32;
	tex.size_line = 128;
	tex.endian = 0;
	tex.img = mlx_xpm_file_to_image(game->mlx, "images/wall_3d.xpm", &tex.width, &tex.height);
	if (!tex.img)
		return ;
	tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.size_line,
			&tex.endian); 
}