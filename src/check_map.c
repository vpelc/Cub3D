/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:14:09 by dbajeux           #+#    #+#             */
/*   Updated: 2025/03/06 00:19:42 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_char_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->mapinfo->map[i])
	{
		j = 0;
		while (game->mapinfo->map[i][j])
		{
			if (game->mapinfo->map[i][j] != '0'
				&& game->mapinfo->map[i][j] != '1'
				&& game->mapinfo->map[i][j] != 'N'
				&& game->mapinfo->map[i][j] != 'S'
				&& game->mapinfo->map[i][j] != 'E'
				&& game->mapinfo->map[i][j] != 'W'
				&& !ft_isspace(game->mapinfo->map[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	check_double_pos_start(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = -1;
	while (game->mapinfo->map[i])
	{
		j = 0;
		while (game->mapinfo->map[i][j])
		{
			if (game->mapinfo->map[i][j] == 'N'
				|| game->mapinfo->map[i][j] == 'S'
				|| game->mapinfo->map[i][j] == 'E'
				|| game->mapinfo->map[i][j] == 'W')
			{
				if (flag == 1)
					return (ft_putstr_fd("Error : Found mutilple start pos\n",
							2), FALSE);
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (flag == -1)
		return (ft_putstr_fd("Error : no start pos in Map\n", 2), FALSE);
	return (TRUE);
}

int	get_map_width(char **map)
{
	int	max_width;
	int	width;
	int	i;

	i = 0;
	max_width = 0;
	width = 0;
	while (map[i])
	{
		width = ft_strlen(map[i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	return (max_width);
}
// void fill_flood(char **map, int x, int y)
// {
// 	if (map[y][x])
// 		(ft_putstr_fd("ici",1));
//     // Calculer la hauteur de la carte (nombre de lignes)
//     int max_y = 0;
//     while (map[max_y])  // Compter le nombre de lignes
//         max_y++;

//     // Vérification si (x, y) est dans les limites de la carte
//     if (y < 0 || y >= max_y)
//         return;

//     // Calculer la largeur de la ligne courante (en fonction de y)
//     int max_x = ft_strlen(map[y]);  // Largeur de la ligne y

//     // Si (x, y) est hors limites, retourner
//     if (x < 0 || x >= max_x)
//         return;

//     // Marquer la position actuelle comme visitée
//     if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == ' ')
//         return;  // Si c'est un mur ('1'), un endroit déjà visité ('F'), ou un espace (' '), ne pas continuer

//     map[y][x] = 'F';  // Marque le terrain comme inondé

//     // Appels récursifs pour les quatre directions
//     if (y - 1 >= 0 && map[y - 1][x] != '1' && map[y - 1][x] != 'F' && map[y - 1][x] != ' ')
//         fill_flood(map, x, y - 1);  // Haut
//     if (y + 1 < max_y && map[y + 1][x] != '1' && map[y + 1][x] != 'F' && map[y + 1][x] != ' ')
//         fill_flood(map, x, y + 1);  // Bas
//     if (x - 1 >= 0 && map[y][x - 1] != '1' && map[y][x - 1] != 'F' && map[y][x - 1] != ' ')
//         fill_flood(map, x - 1, y);  // Gauche
//     if (x + 1 < max_x && map[y][x + 1] != '1' && map[y][x + 1] != 'F' && map[y][x + 1] != ' ')
//         fill_flood(map, x + 1, y);  // Droite
// }

// int check_fill_flood(char **map_copy, int start_x, int start_y)
// {
//     int max_y = 0;
//     while (map_copy[max_y])  // Calculer le nombre de lignes
//         max_y++;

//     // Vérifier si start_y est dans les limites de la carte
//     if (start_y < 0 || start_y >= max_y)
//         return FALSE;

//     int max_x = ft_strlen(map_copy[start_y]);  // Largeur de la ligne courante

//     // Vérification des indices de départ (start_x et start_y)
//     if (start_x < 0 || start_x >= max_x)
//         return FALSE;

//     // Vérifier si la case de départ est valide
//     if (map_copy[start_y][start_x] == ' ' || map_copy[start_y][start_x] == '1')
//         return FALSE;

//     int i = 0;
//     int j;
//     while (i < max_y)
//     {
//         j = 0;
//         int line_length = ft_strlen(map_copy[i]);  // Largeur de la ligne i
//         while (j < line_length)
//         {
//             // Si une case marquée 'F' est touchée et qu'il n'y a pas de murs autour
//             if (map_copy[i][j] == 'F')
//             {
//                 // Vérification des cases adjacentes (haut, bas, gauche, droite)
//                 if (i - 1 >= 0 && j < (int)ft_strlen(map_copy[i - 1]) && map_copy[i - 1][j] != '1' && map_copy[i - 1][j] != 'F') 
//                     return FALSE; // Case au dessus n'est pas un mur ou une case inondée
//                 if (i + 1 < max_y && j < (int)ft_strlen(map_copy[i + 1]) && map_copy[i + 1][j] != '1' && map_copy[i + 1][j] != 'F') 
//                     return FALSE; // Case en dessous n'est pas un mur ou une case inondée
//                 if (j - 1 >= 0 && map_copy[i][j - 1] != '1' && map_copy[i][j - 1] != 'F') 
//                     return FALSE; // Case à gauche n'est pas un mur ou une case inondée
//                 if (j + 1 < line_length && map_copy[i][j + 1] != '1' && map_copy[i][j + 1] != 'F') 
//                     return FALSE; // Case à droite n'est pas un mur ou une case inondée

//                 // Vérifier s'il reste des espaces vides à l'intérieur de l'enclos
//                 if (map_copy[i][j] == ' ')
//                     return FALSE; // Si une case vide est trouvée à l'intérieur de la zone, retourner 0
//             }
//             j++;
//         }
//         i++;
//     }

//     return TRUE; // Tout est valide, tout est correctement enfermé et aucune case vide n'a été trouvée
// }

void fill_flood(char **map, int y, int x,int *flag,t_game *game)
{
	if (y < 0 || y >= game->mapinfo->map_number_line || x < 0 || x >= (int)ft_strlen(map[y]))
		return;
	if (*flag == 1 && map[y][x] == ' ')
		*flag = 0;
	if (*flag == 1 && map[y][x] == '0' && (y == 0 || y == game->mapinfo->map_number_line - 1 || x == 0 || x == (int)ft_strlen(map[y]) - 1))
		*flag = 0;
	map[y][x] = 'F';
	if (y  + 1< game->mapinfo->map_number_line && (int)ft_strlen(map[y + 1]) > x && map[y+1][x] != 'F' && map[y+1][x] != '1')
		fill_flood(map, y + 1, x,flag,game);
	if (y > 0 && (int)ft_strlen(map[y - 1]) > x && map[y - 1][x] != 'F' && map[y - 1][x] != '1')
		fill_flood(map, y - 1, x,flag,game);
	if (x + 1 < (int)ft_strlen(map[y]) && map[y][x + 1] != 'F' && map[y][x + 1] != '1')
		fill_flood(map, y, x + 1,flag,game);
	if (x > 0 && map[y][x - 1] != 'F' && map[y][x - 1] != '1')
		fill_flood(map, y, x - 1,flag,game);
}

char	**copy_map(char **map, int height)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	while (i < height)
	{
		new_map[i] = ft_strdup(map[i]);
		i++;
	}
	new_map[height] = NULL;
	return (new_map);
}

int	get_pos_x_player(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while ((map[i][j]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S')
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

int	get_pos_y_player(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while ((map[i][j]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

// void fill_space(char **map)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j =0;
// 	while (map[i])
// 	{
// 		while(map[i][j])
// 		{
// 			if (ft_imap[i][j])
// 			j++;
// 		}
// 		i++;
// 	}
// }
int	check_map_fully_enclosed(t_game *game)
{
	char **map_copy;
	int flag;
	int start_y;
	int start_x;
	map_copy = copy_map(game->mapinfo->map, game->mapinfo->map_number_line);
	flag = 1;
	if (!map_copy)
		return (ft_putstr_fd("Error : malloc copy map\n", 2), FALSE);
	start_y = get_pos_y_player(map_copy);
	start_x = get_pos_x_player(map_copy);
	fill_flood(map_copy, start_y,start_x,&flag,game);
	if (flag == 0)
	{
		free_tab(map_copy);
		return (ft_putstr_fd("Error map not fully enclosed\n", 2), FALSE);
	}
	free_tab(map_copy);
	return (TRUE);
}