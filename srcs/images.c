/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:11:53 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/25 13:57:34 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	place_tile(mlx_t *mlx, t_map *map, t_grid *pos, t_images *images)
{
	if (pos->tile == '1')
	{
		pos->tile_inst = mlx_image_to_window(mlx, images->wall_img, pos->y * map->tile_size, pos->x * map->tile_size);
		pos->tile_img = images->wall_img;
	}
	else // when pos->tile == '0'
	{
		pos->tile_inst = mlx_image_to_window(mlx, images->floor_img, pos->y * map->tile_size, pos->x * map->tile_size);
		pos->tile_img = images->floor_img;
	}
	if (pos->tile_inst == -1)
		return (0);
	return (1);
}

int	place_object(mlx_t *mlx, t_map *map, t_grid *pos, t_images *images)
{
	if (pos->tile != 'E' && pos->tile != 'C')
		return (1);
	if (pos->tile == 'E')
	{
		pos->obj_inst = mlx_image_to_window(mlx, images->exit_img, pos->y * map->tile_size, pos->x * map->tile_size);
		pos->obj_img = images->exit_img;
	}
	else if (pos->tile == 'C')
	{
		pos->obj_inst = mlx_image_to_window(mlx, images->coin_img, pos->y * map->tile_size, pos->x * map->tile_size);
		pos->obj_img = images->coin_img;
	}
	if (pos->obj_inst == -1)
		return (0);
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
	return (1);
}

int	place_images(mlx_t *mlx, t_map *map, t_images *images)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->scale[0])
	{
		y = 0;
		while (y < map->scale[1])
		{
			if (place_tile(mlx, map, &map->grid[y][x], images) == 0)
				return (0);
			if (place_object(mlx, map, &map->grid[y][x], images) == 0)
				return (0);
			if (place_player(mlx, map, &map->grid[y][x], images) == 0)
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	resize_images(t_images images, t_map *map)
{
	int	new_size;
	
	new_size = map->tile_size;
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

mlx_image_t	*init_img(mlx_t *mlx, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t	*image;

	texture = mlx_load_png(file);
	if (texture == 0)
		return (0);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}

int init_images(mlx_t *mlx, t_map *map)
{
	map->images.player_img = init_img(mlx, PLAYER_TEXTURE);
	map->images.floor_img = init_img(mlx, FLOOR_TEXTURE);
	map->images.wall_img = init_img(mlx, WALL_TEXTURE);
	map->images.exit_img = init_img(mlx, EXIT_TEXTURE);
	map->images.coin_img = init_img(mlx, COIN_TEXTURE);
	if (!map->images.player_img || !map->images.floor_img 
	|| !map->images.wall_img || !map->images.exit_img || !map->images.coin_img)
		return (0);
	if (resize_images(map->images, map) == 0)
		return (0);
	if (place_images(mlx, map, &map->images) == 0)
		return (0);
	return (1);
}

