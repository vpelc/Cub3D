/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:34:32 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/26 15:20:44 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void print_texinfo(t_texinfo *texinfo)
{
    if (!texinfo)
    {
        printf("Texinfo is NULL\n");
        return;
    }
    printf("--- t_texinfo ---\n");
    printf("NO_path: %s\n", texinfo->NO_path ? texinfo->NO_path : "NULL");
    printf("SO_path: %s\n", texinfo->SO_path ? texinfo->SO_path : "NULL");
    printf("WE_path: %s\n", texinfo->WE_path ? texinfo->WE_path : "NULL");
    printf("EA_path: %s\n", texinfo->EA_path ? texinfo->EA_path : "NULL");
    
    printf("Floor RGB: [%d, %d, %d]\n",
           texinfo->floor[0], texinfo->floor[1], texinfo->floor[2]);

    printf("Ceiling RGB: [%d, %d, %d]\n",
           texinfo->ceiling[0], texinfo->ceiling[1], texinfo->ceiling[2]);

    printf("Hex Floor: %lx\n", texinfo->hex_floor);
    printf("Hex Ceiling: %lx\n", texinfo->hex_ceiling);
}

void print_mapinfo(t_mapinfo *mapinfo)
{
    int i;

    i = 0;
    if (!mapinfo)
    {
        printf("Mapinfo is NULL\n");
        return;
    }
    printf("--- t_mapinfo ---\n");
    printf("File Descriptor: %d\n", mapinfo->fd);
    printf("Map Number Line : %d\n",mapinfo->map_number_line);
    printf("MAP\n");
    while(mapinfo->map[i])
    {
        printf("%s\n",mapinfo->map[i]);
        i++;
    }
}

void print_game(t_game *game)
{
    if (!game)
    {
        printf("Game is NULL\n");
        return;
    }
    printf("--- t_game ---\n");
    printf("MLX Pointer: %p\n", game->mlx);
    printf("Window Pointer: %p\n", game->win);
    
    printf("\n");
    print_mapinfo(game->mapinfo);
    printf("\n");
    print_texinfo(game->texinfo);
}