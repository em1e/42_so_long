/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:37:32 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/27 14:10:23 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	window_input_hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
	{
		ft_printf("Window closed A\n"); // remove
		mlx_close_window(param);
	}
}

void player_key_hooks(mlx_key_data_t keydata, void *param) // works
{
	t_map	*map;
	
	map = param;
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && keydata.action == MLX_PRESS)
	{
		ft_printf("-> moved player up\n"); // remove
		move_player(map, 1, 0);
	}
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) && keydata.action == MLX_PRESS)
	{
		ft_printf("-> moved player down\n"); // remove
		move_player(map, -1, 0);
	}
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) && keydata.action == MLX_PRESS)
	{
		ft_printf("-> moved player right\n"); // remove
		move_player(map, 0, 1);
	}
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) && keydata.action == MLX_PRESS)
	{
		ft_printf("-> moved player left\n"); // remove
		move_player(map, 0, -1);
	}
	ft_printf("- - - - - - - - - - -\n"); // remove
}

void	end_game(t_map *map, mlx_t *mlx, int won)
{
	int	total_moves;
	
	total_moves = map->moves;
	if (won == 1)
	{
		ft_printf("- - - - -✨  VICTORY ✨ - - - - - -\n");
		ft_printf("You've won the game!\n");
		ft_printf("Is winning with %d moves the best you can do?\nWhy not try again?\n", total_moves);
	}
	else if (won == 0)
	{
		ft_printf("Giving up already?\n");
		ft_printf("Why not try again?\n");	
	}
	else 
		ft_printf("error\n");
	free(map);
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	exit(won);
}

int	start_game(t_map *map)
{
	mlx_t	*mlx;
	
	mlx = mlx_init(map->scale[0] * map->tile_size, 
		map->scale[1] * map->tile_size, "so_long", false);
	if (mlx == 0)
		return (game_error(mlx, map, "game error B", -1));
	map->mlx = mlx;
	window_size_limit(mlx, map);
	if (init_images(mlx, map) == 0)
		return (game_error(mlx, map, "unable to load images", -1));
	mlx_key_hook(mlx, &player_key_hooks, map); 
	if (mlx_loop_hook(mlx, &window_input_hook, mlx) == 0)
		return (game_error(mlx, map, "game error B", -1));
	if (mlx_loop_hook(mlx, &anim_update_hook, map) == 0)
		return (game_error(mlx, map, "game error B", -1));
	ft_printf("- - - game started - - -\n\n"); // remove
	mlx_loop(mlx);
	mlx_terminate(mlx);
	ft_printf("Window closed B\n"); // remove
	return (1);
}
