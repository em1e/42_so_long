/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:08:16 by vkettune          #+#    #+#             */
/*   Updated: 2024/04/27 03:50:32 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		while (line[j] != 0 && line[j] != '\n')
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
	int		map_fd;

	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
		return (0);
	grid = malloc(sizeof(t_grid *) * scale[1] + 1);
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
	return (grid);
}
