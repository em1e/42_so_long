/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:14:50 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/10 22:32:02 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	wake_enemy(t_map *map, int y, int x)
{
	t_enemy	*enemy;
	mlx_image_t	*awake_img;
	mlx_image_t	*img;
	mlx_image_t	*tmp;
	t_grid	*pos;

	enemy = &map->enemy;
	ft_printf("A enemy y: %d, x: %d\n", enemy->y, enemy->x);
	map->enemy.y = map->player.y + y;
	map->enemy.x = map->player.x + x;
	awake_img = map->images.e_awake_im;
	img = map->enemy.img;
	ft_printf("B enemy y: %d, x: %d\n", enemy->y, enemy->x);
	pos = &map->grid[enemy->y][enemy->x];
	tmp = awake_img;
	// ft_printf("is enemy awake: %d\n", enemy->awake);
	// ft_printf("should be 0.\n");
	if (enemy->awake == 1)
		return ;
	ft_memcpy(img->pixels, awake_img->pixels,
		img->width * img->height * sizeof(int32_t));
	enemy->awake = 1;
	ft_printf("You woke the enemy!\n");
}

void	enemy_fall_asleep(t_map *map)
{
	t_enemy	*enemy;
	mlx_image_t	*asleep_img;
	mlx_image_t	*img;
	mlx_image_t	*tmp;
	t_grid	*pos;

	enemy = &map->enemy;
	asleep_img = map->images.e_asleep_im;
	img = map->enemy.img;
	ft_printf("AA enemy y: %d, x: %d\n", enemy->y, enemy->x);
	pos = &map->grid[enemy->y][enemy->x];
	tmp = asleep_img;
	// ft_printf("is enemy awake: %d\n", enemy->awake);
	// ft_printf("should be 1.\n");
	if (enemy->awake == 0)
		return ;
	ft_memcpy(img->pixels, asleep_img->pixels,
		img->width * img->height * sizeof(int32_t));
	enemy->awake = 0;
	ft_printf("The enemy fell asleep!\n");
}

void	is_enemy(t_map *map)
{
	t_player	*player;
	t_enemy		*enemy;

	player = &map->player;
	enemy = &map->enemy;
	if ((player->y + 1) == enemy->y && player->x == enemy->x)
		wake_enemy(map, 0, 1);
	else if ((player->y - 1) == enemy->y && player->x == enemy->x)
		wake_enemy(map, 0, -1);
	else if (player->y == enemy->y && (player->x + 1) == enemy->x)
		wake_enemy(map, 1, 0);
	else if (player->y == enemy->y && (player->x - 1) == enemy->x)
		wake_enemy(map, -1, 0);
	else if (enemy->awake == 1)
		enemy_fall_asleep(map);
}

void	found_enemy(t_map *map, int y, int x)
{
	t_enemy	*enemy;

	enemy = &map->enemy;
	enemy->y = y;
	enemy->x = x;
	map->enemy.amount++;
}
// found_enemy(map, map->scale[1], i);