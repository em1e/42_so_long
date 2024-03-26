/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:37:32 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/26 14:20:20 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;
    
	if (argc < 2)
		return (error("no map argument given, use format: ./so_long [map]"));
	if (argc > 2)
		return (error("too many arguments, use format: ./so_long [map]"));
	map = parse_map(argv[1]);
	if (map == 0)
		return (1);
	ft_printf("Map parsed\n");
	if (start_game(map) == 0)
		return (1);
	free_map(map);
	ft_printf("map freed\n");
	return (0);
}
