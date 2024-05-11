/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:37:32 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/29 12:58:13 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc < 2)
		return (error("no map argument given, use format: ./so_long [map]"));
	if (argc > 2)
		return (error("too many arguments, use format: ./so_long [map]"));
	map = init_map(argv[1]);
	if (map == 0)
		return (1);
	if (start_game(map) == 0)
		return (1);
	return (0);
}
