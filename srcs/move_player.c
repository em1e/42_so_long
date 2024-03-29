/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:00:15 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/28 13:34:32 by vkettune         ###   ########.fr       */
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

int	move_direction(int direction)
{
	if (direction == 2 || direction == 4) 
		return (-1);
	if (direction == 1 || direction == 3)
		return (1);
	return (2);
}

void move_player(t_map *map, int direction) 
{
	t_grid	target_pos;
	int			move_direc;
	
	if (direction == UP || direction == DOWN)
	{
		move_direc = move_direction(direction);
		target_pos = move_vertically(map, move_direc);
	}
	if (direction == RIGHT || direction == LEFT)
	{
		move_direc = move_direction(direction);
		target_pos = move_horizontally(map, move_direc);
	}
	map->moves++;
	if (map->won == 0)
		ft_printf("Moves: %d\n", map->moves);
	if (direction == UP || direction == DOWN)
		move_player_texture(map, move_direc, 0); // rewrite
	if (direction == RIGHT || direction == LEFT)
		move_player_texture(map, 0, move_direc); // rewrite
	if (target_pos.tile == 'E' && map->collectables == 0)
	{
		map->won = 1;
		end_game(map, map->mlx, map->won);
	}
}

t_grid move_vertically(t_map *map, int move_direc)
{
	t_grid			target_pos;
	t_player		*player;
	
	player = &map->player;
	target_pos = map->grid[player->y - move_direc][player->x];
	ft_printf("coins to collect: %d\n", map->collectables);
	if (target_pos.tile == '1' || (target_pos.tile == 'E' && map->collectables != 0))
	{
		ft_printf("unable to go there!\n"); // remove
		return ;
	}
	if (target_pos.tile == 'C')
		collect(map, player->y - move_direc, player->x);
	map->grid[player->y][player->x].tile = '0';
	player->y -= move_direc;
	map->grid[player->y][player->x].tile = 'P';
	return (target_pos);
}

t_grid	move_horizontally(t_map *map, int move_direc)
{
	t_grid			target_pos;
	t_player		*player;

	player = &map->player;
	target_pos = map->grid[player->y][player->x + move_direc];
	ft_printf("coins to collect: %d\n", map->collectables);
	if (target_pos.tile == '1' || (target_pos.tile == 'E' && map->collectables != 0))
		return (target_pos);
	if (target_pos.tile == 'C')
		collect(map, player->y, player->x + move_direc);
	map->grid[player->y][player->x].tile = '0';
	player->x += move_direc;
	map->grid[player->y][player->x].tile = 'P';
	return (target_pos);
}