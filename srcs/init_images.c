/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:11:53 by vkettune          #+#    #+#             */
/*   Updated: 2024/04/25 16:03:58 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*load_img(mlx_t *mlx, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(file);
	if (texture == 0)
		return (0);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}

int	init_images(mlx_t *mlx, t_map *map)
{
	map->images.random = 1;
	map->images.player_im = load_img(mlx, PLAYER);
	map->images.floor_im = load_img(mlx, FLOOR);
	map->images.wall_im = load_img(mlx, WALL);
	map->images.exit_im = load_img(mlx, DOOR);
	map->images.coin_im = load_img(mlx, COIN);
	if (!map->images.player_im || !map->images.floor_im
		| !map->images.wall_im || !map->images.exit_im || !map->images.coin_im)
		return (0);
	if (resize_images(map->images, map) == 0)
		return (0);
	if (place_images(mlx, map, &map->images) == 0)
		return (0);
	return (1);
}
