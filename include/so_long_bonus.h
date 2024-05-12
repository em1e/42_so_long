/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:03:48 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/12 08:48:44 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

# define TILE_SIZE 50

# define DELAY 0.2
# define DOOR_COOLDOWN 2

# define FLOOR "./textures/floor.png"
# define WALL "./textures/wall.png"
# define DOOR_CLOSED "./textures/door_animation/door_closed.png"
# define DOOR_OPEN "./textures/door_animation/door_open.png"

# define PLAYER_IDLE1 "./textures/pirate/Idle1.png"
# define PLAYER_IDLE2 "./textures/pirate/Idle2.png"
# define PLAYER_IDLE3 "./textures/pirate/Idle3.png"
# define PLAYER_IDLE4 "./textures/pirate/Idle4.png"
# define PLAYER_IDLE5 "./textures/pirate/Idle5.png"

# define ENEMY_1 "./textures/enemy/asleep.png"
# define ENEMY_2 "./textures/enemy/awake.png"

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
	mlx_texture_t	*e_asleep_tx;
	mlx_texture_t	*e_awake_tx;
	mlx_texture_t	*floor_tx;
	mlx_texture_t	*wall_tx;
	mlx_texture_t	*door_tx;
	mlx_texture_t	*coin_tx;
}	t_textures;

typedef struct s_images
{
	mlx_image_t	*player_im;
	mlx_image_t	*e_asleep_im;
	mlx_image_t	*e_awake_im;
	mlx_image_t	*floor_im;
	mlx_image_t	*wall_im;
	mlx_image_t	*coin_im;
	mlx_image_t	*door_closed;
	mlx_image_t	*door_open;
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
	int					exit[2];
}	t_grid;

typedef struct s_player
{
	int					x;
	int					y;
	mlx_image_t			*img;
	int					inst;
}	t_player;

typedef struct s_enemy
{
	int					amount;
	int					x;
	int					y;
	int					awake;
	mlx_image_t			*img;
	int					inst;
}	t_enemy;

typedef struct s_map
{
	t_grid		**grid;
	mlx_t		*mlx;
	t_player	player;
	t_enemy		enemy;
	t_images	images;
	int			exit[2];
	int			scale[2]; // height 0, width 1
	int			direction; // 0 up, 1 dowm, 2 right, 3 left
	int			collectables;
	int			moves;
	int			won;
	int			tile_size;
	int			player_size[2]; // height 0, width 1
	int			item_size;
	int			action; // idle 0, walking 1, opendoor 2
	int			map_fd;
	mlx_image_t	*door_open;
	mlx_image_t	*player_animation[5];
	mlx_image_t	*move_img;
}	t_map;

// animate_door.c
void			open_door(t_map *map);
void			find_door(t_map *map, int scale[], int exit[]);

// animate_player.c
int				init_player_animation(mlx_t *mlx, t_map *map);
void			animate_player(t_map *map);

// check_path.c
int				find_path(t_grid **grid, int y, int x);
void			clean_grid(t_grid **grid, int scale[]);
int				check_path(t_grid **grid, int scale[], int y, int x);

// coin_img.c
char			*find_file(int random);
mlx_image_t		*change_coin_img(mlx_t *mlx, t_map *map);

// enemy.c
void			is_enemy(int keydata, t_map *map, int kill);
void			wake_enemy(t_map *map, int y, int x);
void			enemy_fall_asleep(t_map *map);
void			found_enemy(t_map *map, int y, int x);
void			kill_enemy(t_map *map, int y, int x);

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
void			anim_update_hook(void *param);

// init_grid.c
int				check_walls(t_grid **grid, int scale[], int y, int x);
int				check_grid(t_map *map, t_grid **grid, int scale[], t_player *player);
int				fill_grid(t_grid **grid, int scale[], int map_fd);
t_grid			**init_grid(t_map *map, char *file, int scale[], t_player *player);

// init_images.c
mlx_image_t		*load_img(mlx_t *mlx, char *file);
int				init_images(mlx_t *mlx, t_map *map);

// init_map.c
int				check_line(t_map *map, char *line, int pce[], int width);
int				check_map_content(t_map *map, int scale[]);
int				check_map(t_map *map, char *file, int scale[]);
t_map			*init_map(char *file);

// inst.c
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

// place_moves.c
int				center_text(t_map *map, int width);
void			print_movements(t_map *map);

// resize.c
void			window_size_limit(mlx_t *mlx, t_map *map);
void			resize_tiles(int width, int height, t_map *map);
int				resize_player_animation(mlx_image_t *images[], int new_size);
int				resize_images(t_images images, t_map *map);

#endif
