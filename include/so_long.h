/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:36:09 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/16 08:28:54 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

# define TILE_SIZE 50

# define FLOOR "./textures/floor.png"
# define WALL "./textures/wall.png"
# define DOOR "./textures/door_animation/door_open.png"
# define PLAYER "./textures/pirate/Idle1.png"

# define COIN "./textures/collectable/coin.png"
# define ITEM_1 "./textures/collectable/item1.png"
# define ITEM_2 "./textures/collectable/item2.png"
# define ITEM_3 "./textures/collectable/item3.png"
# define ITEM_4 "./textures/collectable/item4.png"
# define ITEM_5 "./textures/collectable/item5.png"
# define ITEM_6 "./textures/collectable/item6.png"
# define ITEM_7 "./textures/collectable/item7.png"
# define ITEM_8 "./textures/collectable/item8.png"
# define ITEM_9 "./textures/collectable/item9.png"
# define ITEM_10 "./textures/collectable/item10.png"
# define ITEM_11 "./textures/collectable/item11.png"

typedef struct s_textures
{
	mlx_texture_t	*player_tx;
	mlx_texture_t	*floor_tx;
	mlx_texture_t	*wall_tx;
	mlx_texture_t	*exit_tx;
	mlx_texture_t	*collectable_tx;
}	t_textures;

typedef struct s_images
{
	mlx_image_t	*player_im;
	mlx_image_t	*floor_im;
	mlx_image_t	*wall_im;
	mlx_image_t	*exit_im;
	mlx_image_t	*coin_im;
	int			random;
}	t_images;

typedef struct s_grid
{
	int					x;
	int					y;
	char				tile;
	mlx_image_t			*tile_img;
	mlx_image_t			*obj_img;
	int					tile_inst;
	int					obj_inst;
}	t_grid;

typedef struct s_player
{
	int					x;
	int					y;
	mlx_image_t			*img;
	int					inst;
}	t_player;

typedef struct s_map
{
	t_grid		**grid;
	mlx_t		*mlx;
	t_player	player;
	t_images	images;
	int			scale[2];
	int			collectables;
	int			moves;
	int			won;
	int			tile_size;
	int			player_size[2];
	int			item_size;
}	t_map;

// check_path.c
int				find_path(t_grid **grid, int y, int x);
void			clean_grid(t_grid **grid, int scale[]);
int				check_path(t_grid **grid, int scale[], int y, int x);

// coin_img.c
char			*find_file(int random);
mlx_image_t		*change_coin_img(mlx_t *mlx, t_map *map);

// error_and_free.c
int				error(char *msg);
int				game_error(mlx_t *mlx, t_map *map, char *msg, int won);
int				free_grid(t_grid **grid);

// game.c
void			end_game(t_map *map, mlx_t *mlx, int won);
int				start_game(t_map *map);

// hooks.c
void			window_input_hook(void *param);
void			key_hooks(mlx_key_data_t keydata, void *param);

// init_grid.c
int				check_walls(t_grid **grid, int scale[], int y, int x);
int				check_grid(t_grid **grid, int scale[], t_player *player);
int				fill_grid(t_grid **grid, int scale[], int map_fd);
t_grid			**init_grid(char *file, int scale[], t_player *player);

// init_images.c
mlx_image_t		*load_img(mlx_t *mlx, char *file);
int				init_images(mlx_t *mlx, t_map *map);

// init_map.c
int				check_line(char *line, int pce[], int width);
int				check_map_content(int map_fd, int scale[]);
int				check_map(char *file, int scale[]);
t_map			*init_map(char *file);

// utils.c
mlx_instance_t	*get_tile(t_map *map, int y, int x);
mlx_instance_t	*get_object(t_map *map, int y, int x);
mlx_instance_t	*get_player(t_map *map);

// main.c
int				main(int argc, char **argv);

// move_player.c
void			collect(t_map *map, int y, int x);
void			move_player_texture(t_map *map, int up, int right);
void			move(t_map *map, int up, int right);
void			move_player(t_map *map, int up, int right);

// place_img.c
int				place_tile(mlx_t *mlx, t_map *map, t_grid *pos,
					t_images *images);
int				place_object(mlx_t *mlx, t_map *map, t_grid *pos,
					t_images *images);
int				place_player(mlx_t *mlx, t_map *map, t_grid *pos,
					t_images *images);
int				place_images(mlx_t *mlx, t_map *map, t_images *images);

// resize.c
void			window_size_limit(mlx_t *mlx, t_map *map);
void			resize_tiles(int width, int height, t_map *map);
int				resize_images(t_images images, t_map *map);

#endif