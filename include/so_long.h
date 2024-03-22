/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:36:09 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/22 08:19:28 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

# ifndef TILE_SIZE
#  define TILE_SIZE 50
# endif
# ifndef FLOOR_TEXTURE
#  define FLOOR_TEXTURE "./textures/floor.png"
# endif
# ifndef WALL_TEXTURE
#  define WALL_TEXTURE "./textures/wall.png"
# endif
# ifndef PLAYER_TEXTURE
#  define PLAYER_TEXTURE "./textures/player.png"
# endif
# ifndef EXIT_TEXTURE
#  define EXIT_TEXTURE "./textures/exit.png"
# endif
# ifndef COLLECTABLE_TEXTURE
#  define COLLECTABLE_TEXTURE "./textures/collectable.png"
# endif

// typedef struct s_map
// {
//     char	**map;
//     int		collectables;
//     int		player;
// }	t_map;

#endif