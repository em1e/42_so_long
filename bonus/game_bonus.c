/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:37:32 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/29 10:15:39 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	start_game(t_map *map)
{
	mlx_t	*mlx;
	
	mlx = mlx_init(map->scale[0] * map->tile_size, 
		map->scale[1] * map->tile_size + 40, "so_long", false);
	if (mlx == 0)
		return (game_error(mlx, map, "mlx init failed", -1));
	map->mlx = mlx;
	window_size_limit(mlx, map);
	if (init_images(mlx, map) == 0)
		return (game_error(mlx, map, "unable to load images", -1));
	mlx_key_hook(mlx, &key_hooks, map); 
	if (mlx_loop_hook(mlx, &window_input_hook, mlx) == 0)
		return (game_error(mlx, map, "window input failed", -1));
	if (mlx_loop_hook(mlx, &anim_update_hook, map) == 0)
		return (game_error(mlx, map, "animation failed", -1));
	ft_printf("- - - game started - - -\n\n"); // remove
	mlx_loop(mlx);
	end_game(map, mlx, map->won);
	return (1);
}
