/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:00:15 by vkettune          #+#    #+#             */
/*   Updated: 2024/04/25 17:08:09 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect(t_map *map, int y, int x)
{
	mlx_instance_t	*object;

	object = get_object(map, y, x);
	ft_printf("1 item collected!\n");
	if (object == 0)
		return ;
	map->collectables--;
	object->enabled = 0;
}

void	move_player_texture(t_map *map, int up, int right)
{
	get_player(map)->y -= up * map->tile_size;
	get_player(map)->x += right * map->tile_size;
}

void	move(t_map *map, int up, int right)
{
	t_grid			target_pos;
	t_player		*player;

	player = &map->player;
	target_pos = map->grid[player->y - up][player->x + right];
	if (map->grid[player->y][player->x].tile == 'p')
		map->grid[player->y][player->x].tile = 'E';
	else
		map->grid[player->y][player->x].tile = '0';
	player->y -= up;
	player->x += right;
	if (target_pos.tile == 'E' && map->collectables != 0)
	{
		map->grid[player->y][player->x].tile = 'p';
		return ;
	}
	map->grid[player->y][player->x].tile = 'P';
}

void	move_player(t_map *map, int up, int right)
{
	t_grid			target_pos;
	t_player		*player;

	player = &map->player;
	target_pos = map->grid[player->y - up][player->x + right];
	if (target_pos.tile == '1')
		return ;
	if (target_pos.tile == 'C')
		collect(map, player->y - up, player->x + right);
	move(map, up, right);
	map->moves++;
	ft_printf("Moves: %d\n", map->moves);
	move_player_texture(map, up, right);
	if (target_pos.tile == 'E' && map->collectables == 0)
	{
		map->won = 1;
		end_game(map, map->mlx, map->won);
	}
}
