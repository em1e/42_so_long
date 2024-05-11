/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_text_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:28:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/04/25 11:21:32 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	center_text(t_map *map, int width)
{
	int	text;

	text = map->moves;
	if (text / 1000 > 0)
		width = (map->scale[0] * 0.5) * TILE_SIZE - 65;
	else if (text / 100 > 0)
		width = (map->scale[0] * 0.5) * TILE_SIZE - 60;
	else if (text / 10 > 0)
		width = (map->scale[0] * 0.5) * TILE_SIZE - 55;
	else
		width = (map->scale[0] * 0.5) * TILE_SIZE - 50;
	return (width);
}

void	print_movements(t_map *map)
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
	map->move_img = mlx_put_string(map->mlx, text, width,
			map->scale[1] * TILE_SIZE + 10);
	map->moves++;
	free(text);
	ft_printf("Moves: %d\n", map->moves);
}
