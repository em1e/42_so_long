/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_player_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:48:50 by vkettune          #+#    #+#             */
/*   Updated: 2024/04/26 10:06:17 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	init_player_animation(mlx_t *mlx, t_map *map)
{
	int		i;
	char	*file[5];

	file[0] = PLAYER_IDLE1;
	file[1] = PLAYER_IDLE2;
	file[2] = PLAYER_IDLE3;
	file[3] = PLAYER_IDLE4;
	file[4] = PLAYER_IDLE5;
	i = 0;
	while (i < 5)
	{
		map->player_animation[i] = load_img(mlx, file[i]);
		if (map->player_animation[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void	animate_player(t_map *map)
{
	static int	i;
	mlx_image_t	*player_img;
	mlx_image_t	*new_img;

	i++;
	if (i > 1)
		i = 0;
	player_img = map->player.img;
	new_img = map->player_animation[i];
	ft_memcpy(player_img->pixels, new_img->pixels,
		player_img->width * player_img->height * sizeof(int32_t));
}
