/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:00:15 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/29 10:20:45 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void collect(t_map *map, int y, int x)
{
	mlx_instance_t	*object;
	
	ft_printf("found coin!\n"); // remove
	object = get_object(map, y, x);
	ft_printf("1 coin collected!\n"); // remove
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

void move(t_map *map, char old_pos, char new_pos, int up, int right)
{
	t_player		*player;
	
	player = &map->player;
	map->grid[player->y][player->x].tile = old_pos;
	player->y -= up;
	player->x += right;
	map->grid[player->y][player->x].tile = new_pos;
}

int	center_text(t_map *map, int width)
{
	int	text;

	text = map->moves;
	if (text / 1000 > 0)
		width = (map->scale[0] * 0.5) * TILE_SIZE - 65; // 20
	else if (text / 100 > 0)
		width = (map->scale[0] * 0.5) * TILE_SIZE - 60; // 15
	else if (text / 10 > 0)
		width = (map->scale[0] * 0.5) * TILE_SIZE - 55; // 10
	else
		width = (map->scale[0] * 0.5) * TILE_SIZE - 50; // 5
	return (width);
}

void print_movements(t_map *map)
{
	char	*text;
	char	*temp;
	int		width;
	
	width = 0;
	temp = ft_itoa(map->moves);
	if (temp == 0)
		return ;
	text = ft_strjoin("Moves: ", temp);
	free(temp);
	width = center_text(map, width);
	mlx_delete_image(map->mlx, map->move_img);
	map->move_img = mlx_put_string(map->mlx, text, width, map->scale[1] * TILE_SIZE + 10);
	map->moves++;
	free(text);
	ft_printf("Moves: %d\n", map->moves);
}

void move_player(t_map *map, int up, int right) 
{
	t_grid			target_pos;
	t_player		*player;
	
	player = &map->player;
	target_pos = map->grid[player->y - up][player->x + right];
	if (target_pos.tile == '1')
		return ;
	if (target_pos.tile == 'C')
		collect(map, player->y - up, player->x + right);
	if (target_pos.tile == 'E' && map->collectables == 0)
	{
		map->won = 1;
		end_game(map, map->mlx, map->won);
	}
	move(map, '0', 'P', up, right);
	print_movements(map);
	move_player_texture(map, up, right);
}
