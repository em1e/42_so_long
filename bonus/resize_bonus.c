/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:45:14 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/21 08:16:06 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	window_size_limit(mlx_t *mlx, t_map *map)
{
	int	monitor_size[2];
	int	scale[2];

	mlx_get_monitor_size(0, &monitor_size[0], &monitor_size[1]);
	if (map->scale[0] * map->tile_size > monitor_size[0]
		|| map->scale[1] * map->tile_size + 40 > monitor_size[1])
	{
		scale[0] = map->scale[0] * map->tile_size;
		scale[1] = map->scale[1] + 40 * map->tile_size;
		resize_tiles(monitor_size[0], monitor_size[1], map);
		mlx_set_window_size(mlx, map->scale[0] * map->tile_size,
			map->scale[1] + 40 * map->tile_size);
	}
}

void	resize_tiles(int width, int height, t_map *map)
{
	int		new_scale;
	int		new_object;

	new_scale = width / map->scale[0];
	if (map->scale[0] * map->tile_size > width)
	{
		new_scale = width / map->scale[0];
		new_object = (width / map->scale[0]) * 0.6;
	}
	if (map->scale[1] * map->tile_size > height)
	{
		new_scale = height / map->scale[1];
		new_object = (height / map->scale[1]) * 0.6;
	}
	map->tile_size = new_scale;
	map->item_size = new_object;
	if (map->scale[0] * map->tile_size > width
		|| map->scale[1] * map->tile_size > height)
		resize_tiles(width, height, map);
}

int	resize_player_animation(mlx_image_t *images[], int new_size)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (mlx_resize_image(images[i], new_size, new_size) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	resize_images(t_images images, t_map *map)
{
	int	new_size;
	int	new_item_size;

	new_size = map->tile_size;
	new_item_size = map->item_size;
	if (mlx_resize_image(images.player_im, new_size, new_size) == 0)
		return (0);
	if (mlx_resize_image(images.floor_im, new_size, new_size) == 0)
		return (0);
	if (mlx_resize_image(images.wall_im, new_size, new_size) == 0)
		return (0);
	if (mlx_resize_image(images.coin_im, new_item_size, new_item_size) == 0)
		return (0);
	if (mlx_resize_image(images.door_closed, new_size, new_size) == 0)
		return (0);
	if (mlx_resize_image(images.door_open, new_size, new_size) == 0)
		return (0);
	return (1);
}
