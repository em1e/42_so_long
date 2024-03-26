/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:36:09 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/26 15:20:49 by vkettune         ###   ########.fr       */
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
	mlx_texture_t	*player_txr;
	mlx_texture_t	*floor_txr;
	mlx_texture_t	*wall_txr;
	mlx_texture_t	*exit_txr;
	mlx_texture_t	*collectable_txr;
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
	int					inst;
}	t_player;

typedef struct s_map
{
	t_grid		**grid;
	mlx_t			*mlx;
	t_player	player;
	t_images	images;
	int				scale[2];
	int				collectables;
	int				moves;
	int				won;
	int				tile_size;
}	t_map;

// error_and_free.c
int	error(char *msg);
int	game_error(mlx_t *mlx, t_map *map, char *msg, int won);
int	free_map(t_map *map);
int	free_grid(t_grid **grid);

// game.c
void	window_input_hook(void *param);
void	player_key_hooks(mlx_key_data_t keydata, void *param);
void	end_game(t_map *map, mlx_t *mlx, int won);
int		start_game(t_map *map);

// get.c
mlx_instance_t	*get_tile(t_map *map, int y, int x);
mlx_instance_t	*get_object(t_map *map, int y, int x);
mlx_instance_t	*get_player(t_map *map);

// grid.c
int	find_path(t_grid **grid, int y, int x);
void	clean_grid(t_grid **grid, int scale[]);
int	check_path(t_grid **grid, int scale[], int y, int x);
int	check_grid(t_grid **grid, int scale[], t_player *player);
int	fill_grid(t_grid **grid, int scale[], int map_fd);

// place_img.c
int	place_tile(mlx_t *mlx, t_map *map, t_grid *pos, t_images *images);
int	place_object(mlx_t *mlx, t_map *map, t_grid *pos, t_images *images);
int	place_player(mlx_t *mlx, t_map *map, t_grid *pos, t_images *images);
int	place_images(mlx_t *mlx, t_map *map, t_images *images);

// resize.c
void	window_size_limit(mlx_t *mlx, t_map *map);
void	resize_tiles(int width, int height, void *param);
int	resize_images(t_images images, int new_size);

// init_images.c
mlx_image_t	*load_img(mlx_t *mlx, char *file);
int	init_images(mlx_t *mlx, t_map *map);

// main.c
int	main(int argc, char **argv);

// map.c
int	check_line(char *line, int pce[], int width);
int	check_map_content(int map_fd, int scale[]);
int	check_map(char *file, int scale[]);
t_grid	**init_grid(char *file, int scale[], t_player *player);
t_map	*parse_map(char *file);

// move_player.c
void	collect(t_map *map, int y, int x);
void	move_player_texture(t_map *map, int up, int right);
void	move_player(t_map *map, int up, int right);

#endif