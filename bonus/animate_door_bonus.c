/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_door_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:48:20 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/21 07:48:59 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	open_door(t_map *map)
{
	mlx_image_t	*door_img;
	mlx_image_t	*new_img;

	door_img = map->images.door_closed;
	new_img = map->images.door_open;
	ft_memcpy(door_img->pixels, new_img->pixels,
		door_img->width * door_img->height * sizeof(int32_t));
}
