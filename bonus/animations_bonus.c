/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:48:50 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/27 16:26:21 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	animate_player(t_map *map)
{
	static int	i;
	mlx_image_t	*player_img;
	mlx_image_t	*animation_img;
	
	i++;
	if (i > 1)
		i = 0;
	player_img = map->player.img;
	animation_img = map->player_animation[i];
	ft_memcpy(player_img->pixels, animation_img->pixels, 
	player_img->height * player_img->width * sizeof(int8_t));
}

void	animate_coin(t_map *map)
{
	static int	i;
	mlx_image_t	*coin_img;
	mlx_image_t	*animation_img;
	
	i++;
	if (i > 1)
		i = 0;
	coin_img = map->images.coin_img;
	animation_img = map->coin_animation[i];
	ft_memcpy(coin_img->pixels, animation_img->pixels, 
	coin_img->height * coin_img->width * sizeof(int8_t));
}

void	anim_update_hook(void *param)
{
	static double	timer;
	t_map	*map;
	mlx_t	*mlx;

	map = param;
	mlx = map->mlx;
	timer += mlx->delta_time;
	if (timer < (double) DELAY)
		return ;
	timer = 0;
	map = param;
	animate_player(map);
	animate_coin(map);
}

// void	animate_player_walk(t_map *map)
// {
// 	static int	i;
// 	mlx_image_t	*player_img;
// 	mlx_image_t	*animation_img;
	
// 	i++;
// 	if (i > 1)
// 		i = 0;
// 	player_img = map->player.img;
// 	animation_img = map->player_animation->player_idle_animation[i];
// 	ft_memcpy(player_img->pixels, animation_img->pixels, 
// 	player_img->height * player_img->width * sizeof(int8_t));
// }

// resize animations
// animate player
// animate coin
// animate door