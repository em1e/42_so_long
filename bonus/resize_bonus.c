/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:45:14 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/27 09:47:27 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	window_size_limit(mlx_t *mlx, t_map *map)
{
	int	monitor_size[2];

	mlx_get_monitor_size(0, &monitor_size[0], &monitor_size[1]);
	if (map->scale[0] * map->tile_size > monitor_size[0] 
	|| map->scale[1] * map->tile_size > monitor_size[1])
	{
		resize_tiles(monitor_size[0], monitor_size[1], map);
		mlx_set_window_size(mlx, map->scale[0] * map->tile_size, map->scale[1] * map->tile_size);
	}
}

void	resize_tiles(int width, int height, void *param)
{
	t_map	*map;
	int	new_scale;

	map = param;
	new_scale = width / map->scale[0];
	if (map->scale[0] * map->tile_size > width)
		new_scale = width / map->scale[0];
	if (map->scale[1] * map->tile_size > height)
		new_scale = width / map->scale[0];
	map->tile_size = new_scale;
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

int	resize_images(t_images images, int new_size)
{
	if (mlx_resize_image(images.player_img, new_size, new_size) == 0)
		return (0);
	if (mlx_resize_image(images.floor_img, new_size, new_size) == 0)
		return (0);
	if (mlx_resize_image(images.wall_img, new_size, new_size) == 0)
		return (0);
	if (mlx_resize_image(images.exit_img, new_size, new_size) == 0)
		return (0);
	if (mlx_resize_image(images.coin_img, new_size, new_size) == 0)
		return (0);
	return (1);
}