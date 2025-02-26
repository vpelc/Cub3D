/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbajeux <dbajeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:45:22 by dbajeux           #+#    #+#             */
/*   Updated: 2025/02/24 21:56:13 by dbajeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_game game;

	init_data(&game);
	if (check_args(argc, argv) == FALSE
		|| check_content_file(&game,argv[1]) == FALSE)
		return (FALSE);
	ft_printf("Prog Run\n");
	print_game(&game);
	return (TRUE);
}