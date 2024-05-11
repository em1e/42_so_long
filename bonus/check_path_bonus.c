/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:49:11 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/10 19:12:26 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	find_path(t_grid **grid, int y, int x)
{
	char	symbol;

	symbol = grid[y][x].tile;
	if (grid[y] == 0 || symbol == 0
			|| symbol == '1' || symbol == 'X' || symbol == 'Y')
		return (0);
	if (symbol == 'D')
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
	int	y;
	int	x;

	y = 0;
	while (y < scale[1])
	{
		x = 0;
		while (x < scale[0])
		{
			if (grid[y][x].tile == 'X')
				grid[y][x].tile = '0';
			if (grid[y][x].tile == 'Y')
				grid[y][x].tile = 'C';
			x++;
		}
		y++;
	}
}

int	check_path(t_grid **grid, int scale[], int y, int x)
{
	if (grid[y][x].tile == 'E' || grid[y][x].tile == 'C')
	{
		if (!find_path(grid, y, x))
			return (error("no valid path to exit"));
		clean_grid(grid, scale);
		grid[y][x].exit[0] = y;
		grid[y][x].exit[1] = x;
	}
	return (1);
}
