/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:10:26 by vkettune          #+#    #+#             */
/*   Updated: 2024/04/27 04:27:57 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*find_file(int random)
{
	if (random == 0)
		return (COIN);
	else if (random == 1)
		return (ITEM_1);
	else if (random == 2)
		return (ITEM_2);
	else if (random == 3)
		return (ITEM_3);
	else if (random == 4)
		return (ITEM_4);
	else if (random == 5)
		return (ITEM_5);
	else if (random == 6)
		return (ITEM_6);
	else if (random == 7)
		return (ITEM_7);
	else if (random == 8)
		return (ITEM_8);
	else if (random == 9)
		return (ITEM_9);
	else if (random == 10)
		return (ITEM_10);
	else if (random == 11)
		return (ITEM_11);
	return (0);
}

mlx_image_t	*change_coin_img(mlx_t *mlx, t_map *map)
{
	char	*file;

	file = find_file(map->images.random);
	map->images.coin_im = load_img(mlx, file);
	if (map->images.random == 11)
		map->images.random = 0;
	else
		map->images.random++;
	if (!map->images.coin_im)
		return (0);
	if (resize_images(map->images, map) == 0)
		return (0);
	return (map->images.coin_im);
}
