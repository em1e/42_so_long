/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:14:50 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/12 10:45:10 by vkettune         ###   ########.fr       */
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
	map->enemy.y = map->player.y + y;
	map->enemy.x = map->player.x + x;
	awake_img = map->images.e_awake_im;
	img = map->enemy.img;
	// ft_printf("AA enemy y: %d, x: %d\n", enemy->y, enemy->x);
	pos = &map->grid[enemy->y][enemy->x];
	tmp = awake_img;
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
	// ft_printf("BB enemy y: %d, x: %d\n", enemy->y, enemy->x);
	pos = &map->grid[enemy->y][enemy->x];
	tmp = asleep_img;
	if (enemy->awake == 0)
		return ;
	ft_memcpy(img->pixels, asleep_img->pixels,
		img->width * img->height * sizeof(int32_t));
	enemy->awake = 0;
	ft_printf("The enemy fell asleep!\n");
}

void	is_enemy(int keydata, t_map *map, int kill)
{
	t_player	*player;
	t_enemy		*enemy;

	player = &map->player;
	enemy = &map->enemy;
	// ft_printf("Is enemy close?\n");
	if ((player->y + 1) == enemy->y && player->x == enemy->x
		&& !kill)
		wake_enemy(map, 0, 1);
	else if ((player->y - 1) == enemy->y && player->x == enemy->x
		&& !kill)
		wake_enemy(map, 0, -1);
	else if (player->y == enemy->y && (player->x + 1) == enemy->x
		&& !kill)
		wake_enemy(map, 1, 0);
	else if (player->y == enemy->y && (player->x - 1) == enemy->x
		&& !kill)
		wake_enemy(map, -1, 0);
	else if (enemy->awake == 1 && keydata != MLX_KEY_SPACE)
		enemy_fall_asleep(map);
	if (enemy->awake == 1 && keydata == MLX_KEY_SPACE && kill)
		kill_enemy(map, enemy->y, enemy->x);
}

void	kill_enemy(t_map *map, int y, int x)
{
	t_enemy	*enemy;
	t_grid *pos;

	enemy = &map->enemy;
	pos = &map->grid[y][x];
	ft_printf("You killed an enemy near you!\n");
	if (map->grid[y][x].tile == 'D')
	{
		pos->tile_inst = mlx_image_to_window(map->mlx, map->images.floor_im,
			pos->y * map->tile_size, pos->x * map->tile_size);
		pos->tile_img = map->images.floor_im;
		map->grid[y][x].tile = '0';	
	}
	enemy->y = 0;
	enemy->x = 0;
	enemy->awake = 0;
	map->enemy.amount--;
}

void	found_enemy(t_map *map, int y, int x)
{
	t_enemy	*enemy;

	enemy = &map->enemy;
	enemy->y = y;
	enemy->x = x;
}