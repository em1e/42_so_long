/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:21:43 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/25 11:17:32 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_error(char *msg)
{
	char	*a;
	a = msg;
	// ft_printf("Error: %s\n", msg);
	return (-1);
}

int	error(char *msg)
{
	ft_printf("Error: %s\n", msg);
	return (-1);
}

int	game_error(mlx_t *mlx, t_map *map, char *msg)
{
	ft_printf("Error: %s", msg);
	// ft_printf("%s\n", mlx_strerror(mlx_errno));
	free(map);
	if (mlx != 0)
		mlx_terminate(mlx);
	return (-1);
}
