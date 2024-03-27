/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:44:19 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/27 17:37:38 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	init_player_animation(mlx_t *mlx, t_map *map)
{
	int		i;
	char	*file[2];

	file[0] = GOLD_0;
	file[1] = GOLD_1;
	i = 0;
	while (i < 2)
	{
		map->player_animation[i] = load_img(mlx, file[i]);
		if (map->player_animation[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_coin(mlx_t *mlx, t_map *map)
{
	int		i;
	char	*file[2];

	file[0] = COIN_0;
	file[1] = COIN_1;
	i = 0;
	while (i < 2)
	{
		map->coin_animation[i] = load_img(mlx, file[i]);
		if (map->coin_animation[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

// int	init_player_walk(mlx_t *mlx, t_map *map)
// {
// 	int		i;
// 	int		action;
// 	char	*file[6];

// 	file[0] = WALK_0;
// 	file[1] = WALK_1;
// 	file[2] = WALK_2;
// 	file[3] = WALK_3;
// 	file[4] = WALK_4;
// 	file[5] = WALK_5;
// 	i = 0;
// 	action = map->action;
// 	while (i < action)
// 	{
// 		map->player_animation->player_walk_animation[i] = load_img(mlx, file[i]);
// 		if (map->player_animation->player_walk_animation[i] == 0)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
	
// load door animation