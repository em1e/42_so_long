/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 05:46:13 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/10 22:31:52 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check(char *line, int i, int pced[], int width)
{
	if ((i == 0 || i == width - 1) && line[i] != '1')
		return (error("map is not surrounded by walls"));
	if (!ft_strchr("01PCED", line[i]))
		return (error("map contains an invalid character"));
	if (line[i] == 'P' && pced[0] != 0)
		return (error("map contains multiple players"));
	if (line[i] == 'E' && pced[2] != 0)
		return (error("map contains multiple exits"));
	return (1);
}

int	check_line(t_map *map, char *line, int pced[], int width)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (!check(line, i, pced, width))
			return (0);
		if (line[i] == 'P')
			pced[0]++;
		if (line[i] == 'C')
			pced[1]++;
		if (line[i] == 'E')
			pced[2]++;
		if (line[i] == 'D')
		{
			pced[3]++;
			map->enemy.amount++;
			ft_printf("enemy locationnn %d, %d\n", map->enemy.y, map->enemy.x);
		}
		i++;
	}
	if (i != width)
		return (error("map is not rectangular"));
	return (1);
}

int	check_map_content(t_map *map, int scale[])
{
	char	*line;
	int		pced[4];

	line = get_next_line(map->map_fd);
	if (line == 0)
		return (error("map is empty"));
	scale[0] = 0;
	while (line[scale[0]] != '\n' && line[scale[0]] != '\0')
		scale[0]++;
	ft_bzero(pced, 4 * sizeof(int));
	scale[1] = 0;
	while (line != 0)
	{
		if (!check_line(map, line, pced, scale[0]))
		{
			free(line);
			return (0);
		}
		scale[1]++;
		free(line);
		line = get_next_line(map->map_fd);
	}
	if (pced[0] == 0 || pced[1] == 0 || pced[2] == 0 || pced[3] == 0)
		return (error("map is missing a required character"));
	return (pced[1]);
}

int	check_map(t_map *map, char *file, int scale[])
{
	int		map_fd;
	char	*end;
	int		collectables;

	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
		return (error("invalid map_path or map"));
	map->map_fd = map_fd;
	end = ft_strrchr(file, '.');
	if (end == 0 || ft_strncmp(end, ".ber", 5) != 0)
	{
		close(map_fd);
		return (error("map does not end with .ber"));
	}
	collectables = check_map_content(map, scale);
	if (!collectables)
		return (0);
	return (collectables);
}

t_map	*init_map(char *file)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == 0)
		return (0);
	map->collectables = check_map(map, file, map->scale);
	if (map->collectables == 0)
	{
		free(map);
		return (0);
	}
	map->grid = init_grid(file, map->scale, &map->player);
	if (map->grid == 0)
	{
		free(map);
		return (0);
	}
	ft_printf("enemy locationnn %d, %d\n", map->enemy.y, map->enemy.x);
	find_door(map, map->scale, map->exit);
	close(map->map_fd);
	map->tile_size = TILE_SIZE;
	map->item_size = TILE_SIZE * 0.6;
	map->player_size[0] = TILE_SIZE;
	map->player_size[1] = TILE_SIZE * 2;
	map->won = 0;
	return (map);
}
