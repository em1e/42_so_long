/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:14:50 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/17 12:48:34 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	wake_enemy(t_map *map, int x, int y)
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
	ft_printf("AA enemy y: %d, x: %d\n", enemy->y, enemy->x);
	pos = &map->grid[enemy->y][enemy->x];
	ft_printf("AA enemy tile: %c\n", pos->tile);
	tmp = awake_img;
	if (enemy->awake == 1)
		return ;
	map->images.e_asleep_im->instances[map->enemy.inst].enabled = false;
	map->images.e_awake_im->instances[map->enemy.inst2].enabled = true;
	enemy->awake = 1;
	ft_printf("You woke the enemy!\n"); //remove
}

void	enemy_fall_asleep(t_map *map)
{
	t_enemy	*enemy;
	mlx_image_t	*asleep_img;
	t_grid	*pos;

	enemy = &map->enemy;
	asleep_img = map->images.e_asleep_im;
	ft_printf("BB enemy y: %d, x: %d\n", enemy->y, enemy->x); //remove
	pos = &map->grid[enemy->y][enemy->x];
	ft_printf("BB enemy tile: %c\n", pos->tile); //remove
	if (enemy->awake == 0)
		return ;
	map->images.e_asleep_im->instances[map->enemy.inst].enabled = true;
	map->images.e_awake_im->instances[map->enemy.inst2].enabled = false;
	enemy->awake = 0;
	ft_printf("The enemy fell asleep!\n"); //remove
}

void	is_enemy(int keydata, t_map *map, int kill)
{
	t_player	*player;
	t_enemy		*enemy;

	player = &map->player;
	enemy = &map->enemy;
	ft_printf("Is enemy close?\n"); //remove
	ft_printf("enemy at (y, x): %d, %d\n", enemy->y, enemy->x); //remove
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
	{
		kill_enemy(map, enemy->y, enemy->x);
		ft_printf("pos (x, y): %d, %d\n", enemy->x, enemy->y);	
	}
}

void	kill_enemy(t_map *map, int y, int x)
{
	t_enemy	*enemy;
	t_grid *pos;

	enemy = &map->enemy;
	pos = &map->grid[y][x];
	ft_printf("KK enemy y: %d, x: %d\n", y, x);
	ft_printf("KK enemy tile: %c\n", map->grid[y][x].tile);
	if (map->grid[y][x].tile == 'D')
	{
		ft_printf("placing floor tile\n");
		pos->tile_inst = mlx_image_to_window(map->mlx, map->images.floor_im,
			pos->y * map->tile_size, pos->x * map->tile_size);
		pos->tile_img = map->images.floor_im;
		if (pos->tile_inst == -1)
			ft_printf("Error: could not place floor tile\n");
		mlx_set_instance_depth(get_tile(map, pos->x, pos->y), 3);
		map->grid[y][x].tile = '0';	
	}
	ft_printf("You killed an enemy near you!\n");
	ft_printf("Enemies left: %d\n", map->enemy.amount - 1);
	enemy->y = 0;
	enemy->x = 0;
	enemy->awake = 0;
	map->enemy.amount--;
	// ft_printf("KKK enemy tile: %c\n", map->grid[2][1].tile);
}

void	found_enemy(t_map *map, int y, int x)
{
	t_enemy	*enemy;

	enemy = &map->enemy;
	ft_printf("x: %d, y:%d\n", x, y);
	enemy->y = y;
	enemy->x = x;
	ft_printf("x: %d, y:%d\n", enemy->x, enemy->y);
}