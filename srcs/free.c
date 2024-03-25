/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:35:21 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/24 12:58:32 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_map(t_map *map)
{
	free_grid(map->grid);
	free(map);
	return (0);
}

int	free_grid(t_grid **grid)
{
	int	i;

	i = 0;
	while (grid[i] != 0)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	return (0);
}