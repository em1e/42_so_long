/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_door_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:48:20 by vkettune          #+#    #+#             */
/*   Updated: 2024/04/25 11:25:13 by vkettune         ###   ########.fr       */
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

void	find_door(t_map *map, int scale[], int exit[])
{
	int		x;
	int		y;

	y = 0;
	while (y < scale[1])
	{
		x = 0;
		while (x < scale[0])
		{
			if (map->grid[y][x].tile == 'E')
			{
				exit[0] = y;
				exit[1] = x;
				return ;
			}
			x++;
		}
		y++;
	}
}
