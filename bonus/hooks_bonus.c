/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:39:50 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/28 15:40:23 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	window_input_hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
	{
		ft_printf("Window closed - A\n"); // remove
		mlx_close_window(param);
	}
}

void key_hooks(mlx_key_data_t keydata, void *param) // works
{
	t_map	*map;
	
	map = param;
	if (((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && keydata.action == MLX_PRESS) 
	|| (mlx_is_key_down(map->mlx, MLX_KEY_W) || mlx_is_key_down(map->mlx, MLX_KEY_UP)))
	{
		ft_printf("-> moved player up\n"); // remove
		move_player(map, 1, 0);
	}
	if (((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) && keydata.action == MLX_PRESS)
	|| (mlx_is_key_down(map->mlx, MLX_KEY_S) || mlx_is_key_down(map->mlx, MLX_KEY_DOWN)))
	{
		ft_printf("-> moved player down\n"); // remove
		move_player(map, -1, 0);
	}
	if (((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) && keydata.action == MLX_PRESS)
	|| (mlx_is_key_down(map->mlx, MLX_KEY_D) || mlx_is_key_down(map->mlx, MLX_KEY_RIGHT)))
	{
		ft_printf("-> moved player right\n"); // remove
		move_player(map, 0, 1);
	}
	if (((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) && keydata.action == MLX_PRESS)
	|| (mlx_is_key_down(map->mlx, MLX_KEY_A) || mlx_is_key_down(map->mlx, MLX_KEY_LEFT)))
	{
		ft_printf("-> moved player left\n"); // remove
		move_player(map, 0, -1);
	}
}