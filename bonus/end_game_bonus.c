/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:39:10 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/29 10:15:19 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	end_game(t_map *map, mlx_t *mlx, int won)
{
	int	total_moves;
	t_player *player;
	
	player = &map->player;
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
	free_map(map);
	ft_printf("mlx window closed - B\n"); // remove
	mlx_close_window(mlx);
	ft_printf("mlx session terminated\n"); // remove
	mlx_terminate(mlx);
	exit(won);
}