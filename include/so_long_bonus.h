#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

# ifndef TILE_SIZE
#  define TILE_SIZE 32
# endif

#  define DELAY 0.2

#  define FLOOR_TEXTURE "./textures/floor/floor1.png"
#  define WALL_TEXTURE "./textures/wall/wall.png"
#  define PLAYER_TEXTURE "./textures/still_animation/duck_still1.png"
#  define EXIT_TEXTURE "./textures/door_animation/door_closed.png"
#  define COIN_TEXTURE "./textures/collectable/coin.png"

#  define IDLE_0 "./textures/still_animation/duck_still1.png"
#  define IDLE_1 "./textures/still_animation/duck_still2.png"

#  define WALK_0 "./textures/walk_animation/duck_walk1.png"
#  define WALK_1 "./textures/walk_animation/duck_walk2.png"
#  define WALK_2 "./textures/walk_animation/duck_walk3.png"
#  define WALK_3 "./textures/walk_animation/duck_walk4.png"
#  define WALK_4 "./textures/walk_animation/duck_walk5.png"
#  define WALK_5 "./textures/walk_animation/duck_walk6.png"

#  define COIN_0 "./textures/collectable/coin.png"
#  define COIN_1 "./textures/collectable/coin2.png"
#  define GOLD_0 "./textures/collectable/gold.png"
#  define GOLD_1 "./textures/collectable/gold2.png"

#  define DOOR_0 "./textures/collectable/coin.png"
#  define DOOR_1 "./textures/collectable/coin2.png"

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

	mlx_image_t	*idle_animation[2];
	mlx_image_t	*walk_animation[6];
}	t_player;

typedef struct s_animation
{
	mlx_image_t	*player_idle_animation[2];
	mlx_image_t	*player_walk_animation[6];
} t_animation;

typedef struct s_map
{
	t_grid			**grid;
	mlx_t				*mlx;
	t_player		player;
	t_images		images;
	int					scale[2]; // height 0, width 1
	int					collectables;
	int					moves;
	int					won;
	int					tile_size;
	int					action; // idle 0, walking 1, opendoor 2
	mlx_image_t *player_animation[2];
	mlx_image_t	*move_img;
	// mlx_image_t	*coin_animation[2];
	// mlx_image_t	*door_animation[2];
}	t_map;

// error_and_free.c
int	error(char *msg);
int	game_error(mlx_t *mlx, t_map *map, char *msg, int won);
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
void print_movements(t_map *map);

// animations_init.c
int	init_player_animation(mlx_t *mlx, t_map *map);
// int	init_player_walk(mlx_t *mlx, t_map *map);
// int	init_coin(mlx_t *mlx, t_map *map);

// animations.c
int	resize_player_animation(mlx_image_t *images[], int new_size);
void	animate_player(t_map *map);
void	anim_update_hook(void *param);

#endif