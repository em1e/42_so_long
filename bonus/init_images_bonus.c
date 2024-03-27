/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:11:53 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/27 16:29:19 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

mlx_image_t	*load_img(mlx_t *mlx, char *file)
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
	map->images.player_img = load_img(mlx, PLAYER_TEXTURE);
	map->images.floor_img = load_img(mlx, FLOOR_TEXTURE);
	map->images.wall_img = load_img(mlx, WALL_TEXTURE);
	map->images.exit_img = load_img(mlx, EXIT_TEXTURE);
	map->images.coin_img = load_img(mlx, COIN_TEXTURE);
	if (!map->images.player_img || !map->images.floor_img 
	|| !map->images.wall_img || !map->images.exit_img || !map->images.coin_img)
		return (0);
	if (resize_images(map->images, map->tile_size) == 0)
		return (0);
	if (place_images(mlx, map, &map->images) == 0)
		return (0);
	if (init_player_animation(mlx, map) == 0 || init_coin(mlx, map) == 0)
		return (0);
	if (resize_player_animation(map->player_animation, map->tile_size) == 0)
		return (0);
	return (1);
}

