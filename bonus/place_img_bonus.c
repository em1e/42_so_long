/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_img_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:44:16 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/28 15:32:53 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	place_tile(mlx_t *mlx, t_map *map, t_grid *pos, t_images *images)
{
	if (pos->tile == '1')
	{
		pos->tile_inst = mlx_image_to_window(mlx, images->wall_img, pos->y * map->tile_size, pos->x * map->tile_size);
		pos->tile_img = images->wall_img;
	}
	else
	{
		pos->tile_inst = mlx_image_to_window(mlx, images->floor_img, pos->y * map->tile_size, pos->x * map->tile_size);
		pos->tile_img = images->floor_img;
	}
	if (pos->tile_inst == -1)
		return (0);
	mlx_set_instance_depth(get_tile(map, pos->x, pos->y), 0);
	return (1);
}

int	place_object(mlx_t *mlx, t_map *map, t_grid *pos, t_images *images)
{
	if (pos->tile != 'E' && pos->tile != 'C')
		return (1);
	if (pos->tile == 'C')
	{
		pos->obj_inst = mlx_image_to_window(mlx, images->coin_img, pos->y * map->tile_size, pos->x * map->tile_size);
		pos->obj_img = images->coin_img;
	}
	else if (pos->tile == 'E')
	{
		pos->obj_inst = mlx_image_to_window(mlx, images->exit_img, pos->y * map->tile_size, pos->x * map->tile_size);
		pos->obj_img = images->exit_img;
	}
	if (pos->obj_inst == -1)
		return (0);
	mlx_set_instance_depth(get_tile(map, pos->x, pos->y), 5);
	return (1);
}

int	place_player(mlx_t *mlx, t_map *map, t_grid *pos, t_images *images)
{
	if (pos->tile != 'P')
		return (1);
	map->player.inst = mlx_image_to_window(mlx, images->player_img, pos->y * map->tile_size, pos->x * map->tile_size);
	map->player.img = images->player_img;
	if (map->player.inst == -1)
		return (0);
	mlx_set_instance_depth(get_tile(map, pos->x, pos->y), 10);
	return (1);
}

int	place_images(mlx_t *mlx, t_map *map, t_images *images)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->scale[1])
	{
		x = 0;
		while (x < map->scale[0])
		{
			if (place_tile(mlx, map, &map->grid[y][x], images) == 0)
				return (0);
			if (place_object(mlx, map, &map->grid[y][x], images) == 0)
				return (0);
			if (place_player(mlx, map, &map->grid[y][x], images) == 0)
				return (0);
			x++;
		}
		y++;
	}
	print_movements(map);
	return (1);
}