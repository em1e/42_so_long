/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:08:16 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/27 14:41:41 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

int	check_walls(t_grid **grid, int scale[], int y, int x)
{
	if (y == 0 || y == scale[1] - 1)
	{
		if (grid[y][x].tile != '1')
			return (error("map is not surrounded by walls"));
	}
	return (1);
}

int	check_grid(t_grid **grid, int scale[], t_player *player)
{
	int		x;
	int		y;
	
	y = 0;
	while (y < scale[1])
	{
		x = 0;
		while (x < scale[0])
		{
			if (!check_walls(grid, scale, y, x))
				return (0);
			if (!check_path(grid, scale, y, x))
				return (0);
			if (grid[y][x].tile == 'P')
			{
				ft_printf("(x, y): (%d,%d)\n", x, y); // remove
				player->x = x;
				player->y = y;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	fill_grid(t_grid **grid, int scale[], int map_fd)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (i < scale[1])
	{
		line = get_next_line(map_fd);
		if (line == 0)
			return (0);
		j = 0;
		grid[i] = ft_calloc(scale[0] + 1, sizeof(t_grid));
		if (grid[i] == 0)
			return (0);
		while(line[j] != 0 && line[j] != '\n')
		{
			grid[i][j].x = i;
			grid[i][j].y = j;
			grid[i][j].tile = line[j];
			j++;
		}
		free(line);
		i++;
	}
	return (1);
}

t_grid	**init_grid(char *file, int scale[], t_player *player) 
{
	t_grid	**grid;
	int			map_fd;

	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
		return (0);
	grid = ft_calloc(sizeof(t_grid *), scale[1] + 1);
	if (grid == 0)
	{
		close(map_fd);
		return (0);
	}
	if (!fill_grid(grid, scale, map_fd) || !check_grid(grid, scale, player))
	{
		free_grid(grid);
		close(map_fd);
		return (0);
	}
	close(map_fd);
	ft_printf("grid created and filled\n");
	return (grid);
}