/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:08:34 by vkettune          #+#    #+#             */
/*   Updated: 2024/04/25 10:16:06 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	find_path(t_grid **grid, int y, int x)
{
	char	symbol;

	if (grid[y] == 0 || grid[y][x].tile == 0)
		return (0);
	symbol = grid[y][x].tile;
	if (symbol == '1' || symbol == 'X' || symbol == 'Y')
		return (0);
	if (symbol == 'P')
		return (1);
	if (symbol == '0')
		grid[y][x].tile = 'X';
	if (symbol == 'C')
		grid[y][x].tile = 'Y';
	if (find_path(grid, y + 1, x) == 1 || find_path(grid, y - 1, x) == 1)
	{
		grid[y][x].tile = symbol;
		return (1);
	}
	if (find_path(grid, y, x + 1) == 1 || find_path(grid, y, x - 1) == 1)
	{
		grid[y][x].tile = symbol;
		return (1);
	}
	return (0);
}

void	clean_grid(t_grid **grid, int scale[])
{
	int	i;
	int	j;

	i = 0;
	while (i < scale[1])
	{
		j = 0;
		while (j < scale[0])
		{
			if (grid[i][j].tile == 'X')
				grid[i][j].tile = '0';
			if (grid[i][j].tile == 'Y')
				grid[i][j].tile = 'C';
			j++;
		}
		i++;
	}
}

int	check_path(t_grid **grid, int scale[], int y, int x)
{
	if (grid[y][x].tile == 'E' || grid[y][x].tile == 'C')
	{
		if (!find_path(grid, y, x))
			return (error("no valid path to exit"));
		clean_grid(grid, scale);
	}
	return (1);
}
