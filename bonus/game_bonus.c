/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:37:32 by vkettune          #+#    #+#             */
/*   Updated: 2024/04/25 10:58:46 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	end_game(t_map *map, mlx_t *mlx, int won)
{
	int	total_moves;

	total_moves = map->moves;
	if (won == 1)
	{
		ft_printf("- - - - - ✨ VICTORY ✨ - - - - - -\n");
		ft_printf("You've won the game!\n");
		ft_printf("Is winning with %d moves ", total_moves);
		ft_printf("the best you can do?\n");
		ft_printf("- - - - - - - - - - - - - - - - - -\n");
	}
	else if (won == 0)
	{
		ft_printf("- - - - - ❌ GAME OVER ❌ - - - - - -\n");
		ft_printf("The game ended after %d moves.\n", total_moves);
		ft_printf("Why not try again?\n");
		ft_printf("- - - - - - - - - - - - - - - - - - -\n");
	}
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	exit(won);
}

int	start_game(t_map *map)
{
	mlx_t	*mlx;

	mlx = mlx_init(map->scale[0] * map->tile_size,
			map->scale[1] * map->tile_size + 40, "so_long", false);
	if (mlx == 0)
		return (game_error(mlx, map, "mlx fail", -1));
	map->mlx = mlx;
	window_size_limit(mlx, map);
	if (init_images(mlx, map) == 0)
		return (game_error(mlx, map, "unable to load images", -1));
	mlx_key_hook(mlx, &key_hooks, map);
	if (mlx_loop_hook(mlx, &window_input_hook, mlx) == 0)
		return (game_error(mlx, map, "window input hook fail", -1));
	if (mlx_loop_hook(mlx, &anim_update_hook, map) == 0)
		return (game_error(mlx, map, "animation update hook fail", -1));
	ft_printf("- - - game started - - -\n\n");
	mlx_loop(mlx);
	end_game(map, mlx, map->won);
	return (1);
}
