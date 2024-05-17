/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:14:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/17 12:47:43 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

mlx_instance_t	*get_tile(t_map *map, int y, int x)
{
	mlx_image_t		*image;
	int				inst;

	image = map->grid[y][x].tile_img;
	inst = map->grid[y][x].tile_inst;
	return (&image->instances[inst]);
}

mlx_instance_t	*get_object(t_map *map, int y, int x)
{
	mlx_image_t		*image;
	int				inst;

	image = map->grid[y][x].obj_img;
	if (image == 0)
		return (0);
	inst = map->grid[y][x].obj_inst;
	return (&image->instances[inst]);
}

mlx_instance_t	*get_enemy(t_map *map, int num)
{
	mlx_image_t		*image;
	int				inst;

	if (num == 1)
		image = map->images.e_awake_im;
	else
		image = map->images.e_asleep_im;
	if (image == 0)
		return (0);
	if (num == 1)
		inst = map->enemy.inst2;
	else
		inst = map->enemy.inst;
	return (&image->instances[inst]);
}

mlx_instance_t	*get_player(t_map *map)
{
	mlx_image_t	*image;
	int			inst;

	image = map->player.img;
	if (image == 0)
		return (0);
	inst = map->player.inst;
	return (&image->instances[inst]);
}

void place_enemy(mlx_t *mlx, t_map *map, t_grid *pos, t_images *images)
{
	map->enemy.inst = mlx_image_to_window(mlx, images->e_asleep_im,
			pos->y * map->tile_size, pos->x * map->tile_size);
	map->enemy.inst2 = mlx_image_to_window(mlx, images->e_awake_im,
			pos->y * map->tile_size, pos->x * map->tile_size);
	images->e_asleep_im->instances[map->enemy.inst].enabled = true;
	images->e_awake_im->instances[map->enemy.inst2].enabled = false;
	mlx_set_instance_depth(get_enemy(map, 1), 1);
	mlx_set_instance_depth(get_enemy(map, 0), 2);
	if (map->enemy.inst == -1)
		ft_printf("Error: could not place enemy\n");
	if (map->enemy.inst2 == -1)
		ft_printf("Error: could not place enemy\n");
	ft_printf("enemy placed\n");
}
