/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:36:09 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/25 12:59:37 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

# ifndef TILE_SIZE
#  define TILE_SIZE 32
# endif
// # ifndef COIN_SIZE
// #  define COIN_SIZE 10
// # endif
# ifndef FLOOR_TEXTURE
#  define FLOOR_TEXTURE "./textures/floor/floor1.png"
# endif
# ifndef WALL_TEXTURE
#  define WALL_TEXTURE "./textures/wall/wall.png"
# endif
# ifndef PLAYER_TEXTURE
#  define PLAYER_TEXTURE "./textures/still_animation/duck_still1.png"
# endif
# ifndef EXIT_TEXTURE
#  define EXIT_TEXTURE "./textures/door_animation/door_closed.png"
# endif
# ifndef COIN_TEXTURE
#  define COIN_TEXTURE "./textures/collectable/coin.png"
# endif

typedef struct s_textures
{
	mlx_texture_t	*player_tex;
	mlx_texture_t	*floor_tex;
	mlx_texture_t	*wall_tex;
	mlx_texture_t	*exit_tex;
	mlx_texture_t	*collectable_tex;
}	t_textures;

typedef struct s_images
{
	mlx_image_t	*player_img;
	mlx_image_t	*floor_img;
	mlx_image_t	*wall_img;
	mlx_image_t	*exit_img;
	mlx_image_t	*coin_img;
}	t_images;

typedef struct s_grid
{
	int					x;
	int					y;
	char				tile;
	mlx_image_t	*tile_img;
	mlx_image_t	*obj_img;
	int					tile_inst;
	int					obj_inst;
}	t_grid;

typedef struct s_player
{
	int					x;
	int					y;
	mlx_image_t	*img;
	int				inst;
}	t_player;

typedef struct s_map
{
	t_grid	**grid;
	int			scale[2];
	int			collectables;
	int			tile_size;
	t_player	player;
	t_images	images;
}	t_map;

int	error(char *msg);
int	map_error(char *msg);
int	game_error(mlx_t *mlx, t_map *map, char *msg);
int	free_map(t_map *map);
int	free_grid(t_grid **grid);

t_map	*parse_map(char *file);
int	start_game(t_map *map);
t_grid	**init_grid(char *file, int scale[], t_player *player);
int init_images(mlx_t *mlx, t_map *map);
void	window_size_limit(mlx_t *mlx, t_map *map);

void move_player(t_map *map, int up, int right);
int	check_grid(t_grid **grid, int scale[], t_player *player);
int	fill_grid(t_grid **grid, int scale[], int map_fd);

mlx_instance_t	*get_object(t_map *map, int y, int x);
mlx_instance_t	*get_player(t_map *map);

#endif