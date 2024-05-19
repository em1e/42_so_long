/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:14:50 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/19 20:35:38 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	wake_enemy(t_map *map, int x, int y)
{
	t_enemy			*enemy;
	mlx_image_t		*awake_img;
	t_grid			*pos;

	enemy = &map->enemy;
	map->enemy.y = map->player.y + y;
	map->enemy.x = map->player.x + x;
	awake_img = map->images.e_awake_im;
	pos = &map->grid[enemy->y][enemy->x];
	if (enemy->awake == 1)
		return ;
	map->images.e_asleep_im->instances[map->enemy.inst].enabled = false;
	map->images.e_awake_im->instances[map->enemy.inst2].enabled = true;
	enemy->awake = 1;
	ft_printf("You woke up the enemy near you!\n");
}

void	enemy_fall_asleep(t_map *map)
{
	t_enemy			*enemy;
	mlx_image_t		*asleep_img;
	t_grid			*pos;

	enemy = &map->enemy;
	asleep_img = map->images.e_asleep_im;
	pos = &map->grid[enemy->y][enemy->x];
	if (enemy->awake == 0)
		return ;
	map->images.e_asleep_im->instances[map->enemy.inst].enabled = true;
	map->images.e_awake_im->instances[map->enemy.inst2].enabled = false;
	enemy->awake = 0;
	ft_printf("The enemy near you went to sleep!\n");
}

void	is_enemy(int keydata, t_map *map, int kill)
{
	t_player	*player;
	t_enemy		*enemy;

	player = &map->player;
	enemy = &map->enemy;
	if (map->grid[player->y + 1][player->x].tile == 'D' && !kill)
		wake_enemy(map, 0, 1);
	else if (map->grid[player->y - 1][player->x].tile == 'D' && !kill)
		wake_enemy(map, 0, -1);
	else if (map->grid[player->y][player->x + 1].tile == 'D' && !kill)
		wake_enemy(map, 1, 0);
	else if (map->grid[player->y][player->x - 1].tile == 'D' && !kill)
		wake_enemy(map, -1, 0);
	else if (enemy->awake == 1 && !kill)
		enemy_fall_asleep(map);
	if (enemy->awake == 1 && keydata == MLX_KEY_SPACE && kill)
		kill_enemy(map, enemy->y, enemy->x);
}

void	kill_enemy(t_map *map, int y, int x)
{
	t_enemy	*enemy;
	t_grid	*pos;

	enemy = &map->enemy;
	pos = &map->grid[y][x];
	if (map->grid[y][x].tile == 'D')
	{
		pos->tile_inst = mlx_image_to_window(map->mlx, map->images.floor_im,
				pos->y * map->tile_size, pos->x * map->tile_size);
		pos->tile_img = map->images.floor_im;
		if (pos->tile_inst == -1)
			ft_printf("Error: could not place floor tile\n");
		mlx_set_instance_depth(get_tile(map, pos->x, pos->y), 3);
		map->grid[y][x].tile = '0';
	}
	ft_printf("You killed the enemy near you!\n");
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
