/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:00:15 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/25 12:12:44 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void collect(t_map *map, int y, int x)
{
	mlx_instance_t	*object;
	ft_printf("found coin!\n"); // remove
	object = get_object(map, y, x);
	ft_printf("1 coin collected!\n"); // remove
	if (object == 0)
		return ;
	map->collectables--;
	ft_printf("coins to collect: %d\n", map->collectables);
	object->enabled = 0;
}

void	move_player_texture(t_map *map, int up, int right)
{
	get_player(map)->y -= up * map->tile_size;
	get_player(map)->x += right * map->tile_size;
}

void move_player(t_map *map, int up, int right) 
{
	static int	moves;
	static int	won;
	t_grid			target_pos;
	t_player		*player;
	
	player = &map->player;
	ft_printf("at->y: %d\n", player->y); // remove
	ft_printf("at->x: %d\n", player->x); // remove
	target_pos = map->grid[player->y - up][player->x + right];
	ft_printf("coins to collect: %d\n", map->collectables);
	if (target_pos.tile == '1' || (target_pos.tile == 'E' && map->collectables != 0))
	{
		ft_printf("unable to go there!\n"); // remove
		return ;
	}
	if (target_pos.tile == 'C')
		collect(map, player->y - up, player->x + right);
	map->grid[player->y][player->x].tile = '0';
	player->y -= up;
	player->x += right;
	map->grid[player->y][player->x].tile = 'P';
	ft_printf("moved_to->y: %d\n", player->y); // remove
	ft_printf("moved_to->x: %d\n", player->x); // remove
	moves++;
	if (won == 0)
		ft_printf("Moves: %d\n", moves);
	move_player_texture(map, up, right);
	if (target_pos.tile == 'E')
	{
		ft_printf("You won!\n");
		won = 1;
	}
}