/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 05:46:13 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/25 12:59:53 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// check file, file extension, and path/file access
// check collectables, exits, player, walls, and map size

t_grid	**init_grid(char *file, int scale[], t_player *player) 
{
	t_grid	**grid;
	int			map_fd;

	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
		return (0);
	grid = malloc(sizeof(t_grid *) * scale[1] + 1);
	if (grid == 0)
	{
		close(map_fd);
		return (0);
	}
	if (!fill_grid(grid, scale, map_fd) || !check_grid(grid, scale, player)) // player pos not filled correctly
	{
		free_grid(grid);
		close(map_fd);
		return (0);
	}
	close(map_fd);
	ft_printf("grid created and filled\n");
	return (grid);
}

int	check_line(char *line, int pce[], int width)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if ((i == 0 || i == width - 1) && line[i] != '1')
			return (error("map is not surrounded by walls"));
		if (!ft_strchr("01PCE", line[i]))
			return (error("map contains an invalid character"));
		if (line[i] == 'P' && pce[0] > 0)
			return (error("map contains multiple players"));
		if (line[i] == 'E' && pce[2] > 0)
			return (error("map contains multiple exits"));
		if (line[i] == 'P')
			pce[0]++;
		if (line[i] == 'C')
			pce[1]++;
		if (line[i] == 'E')
			pce[2]++;
		i++;
	}
	if (i != width)
		return (map_error("map is not rectangular"));
	return (1);
}

int	check_map_content(int map_fd, int scale[])
{
	char	*line;
	int	pce[3];

	line = get_next_line(map_fd);
	if (line == 0)
		return (error("map is empty"));
	scale[0] = 0;
	while (line[scale[0]] != '\n' && line[scale[0]] != '\0')
		scale[0]++;
	ft_bzero(pce, 3 * sizeof(int));
	scale[1] = 0;
	ft_printf("\n"); // remove
	while (line != 0)
	{
		ft_printf("%s", line); // remove
		if (!check_line(line, pce, scale[0]))
		{
			free(line);
			return (0);
		}
		scale[1]++;
		free(line);
		line = get_next_line(map_fd);
	}
	if (pce[0] == 0 || pce[1] == 0 || pce[2] == 0)
		return (error("map is missing a required character"));
	ft_printf("\ncollectables: %d\n", pce[1]); // remove
	return (pce[1]);
}

int	check_map(char *file, int scale[])
{
	int	map_fd;
	char	*end;
	int collectables;

	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
		return (error("invalid map_path or map"));
	end = ft_strrchr(file, '.');
	ft_printf("end: %s", end); // remove
	if (end == 0 || ft_strncmp(end, ".ber", 5) != 0)
	{
		close (map_fd);
		return (map_error("map does not end with .ber"));
	}
	collectables = check_map_content(map_fd, scale);
	close(map_fd);
	if (!collectables)
		return (-1);
	return (collectables);
}

t_map	*parse_map(char *file)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == 0)
		return (0);
	map->collectables = check_map(file, map->scale);
	if (map->collectables == 0)
	{
		free(map);
		return (0);
	}
	map->grid = init_grid(file, map->scale, &map->player); // fix
	if (map->grid == 0)
	{
		free(map);
		return (0); 
	}
	map->tile_size = TILE_SIZE;
	return (map);
}
