/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:08:16 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/16 16:37:52 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_walls(t_grid **grid, int scale[], int y, int x)
{
	if (y == 0 || y == scale[1] - 1)
	{
		if (grid[y][x].tile != '1')
			return (error("map is not surrounded by walls"));
	}
	return (1);
}

int	check_grid(t_map *map, t_grid **grid, int scale[], t_player *player)
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
				ft_printf("player found at: %d,%d\n", x, y);
				player->x = x;
				player->y = y;
			}
			if (grid[y][x].tile == 'D')
			{
				ft_printf("TEST enemy found at (x, y): %d,%d\n", x, y);
				found_enemy(map, y, x);
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
		ft_printf("line: %s", line);
		free(line);
		i++;
	}
	return (1);
}

t_grid	**init_grid(t_map *map, char *file, int scale[], t_player *player)
{
	t_grid		**grid;
	int			map_fd;

	grid = ft_calloc(sizeof(t_grid *), scale[1] + 1);
	map_fd = open(file, O_RDONLY);
	if (grid == 0 || map_fd == -1)
		return (0);
	if (!fill_grid(grid, scale, map_fd) || !check_grid(map, grid, scale, player))
	{
		free_grid(grid);
		close(map_fd);
		return (0);
	}
	close(map_fd);
	return (grid);
}
