# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 11:14:33 by vkettune          #+#    #+#              #
#    Updated: 2024/03/22 08:26:22 by vkettune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

X = \033[0;39m
BLACK = \033[0;30m
DARK_RED = \033[0;31m
DARK_GREEN = \033[0;32m
DARK_YELLOW = \033[0;33m
DARK_BLUE = \033[0;34m
DARK_MAGENTA = \033[0;35m
DARK_CYAN = \033[0;36m
DARK_GRAY = \033[0;90m
LIGHT_GRAY = \033[0;37m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = so_long
CFLAGS = -Wall -Wextra -Werror $(HEADERS)
HEADERS = -I ./include -I ./libs/MLX42/include/MLX42

LIBFT = ./libs/libft/libft.a
MLX42 = $(MLX42_DIR)build/libmlx42.a
# DEPEND = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

LIBFT_OBJ = ./libs/libft/objs/
MLX42_DIR = ./libs/MLX42/

# LIBS = $(LIBFT) $(MLX42) $(DEPEND)
LIBS = $(MLX42) -Iinclude -lglfw \
		-L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa \
		-framework OpenGL -framework IOKit \
		$(LIBFT)

SRCS_DIR = srcs/
OBJS_DIR = objs/

# FILES = so_long.c game.c player.c map.c check_map.c\
# 	images.c free.c error.c resize.c
FILES = test.c test2.c
SOURCES = $(addprefix $(SRCS_DIR), $(FILES))
OBJECTS = $(addprefix $(OBJS_DIR), $(FILES:.c=.o))

all: folders libft mlx42 $(NAME)
	@echo "$(GREEN)- - - - - - - - - - - - - - - - - - - - - - -$(X)"
	@echo "$(GREEN)Run the program with ./$(NAME)$(X)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@cc $(CFLAGS) -c $< -o $@ && echo "$(DARK_GRAY)Compiled: $@ $(X)"

$(NAME): $(OBJECTS)
	@cc $(OBJECTS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(DARK_MAGENTA)- - ✨✨✨✨ $(NAME) compiled! ✨✨✨✨ - -$(X)"

folders:
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(LIBFT_OBJ)/libft
	@mkdir -p $(LIBFT_OBJ)/ft_printf
	@mkdir -p $(LIBFT_OBJ)/gnl
	@echo "$(DARK_MAGENTA)- - - - - 📁 Created all folders! 📁 - - - - -\n$(X)"

libft:
	@make -C ./libs/libft/ all

clone_mlx42:
	if [ ! -d "$(MLX42_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
		echo "$(DARK_MAGENTA)- - - - - - 📦 MLX42 cloned 📦 - - - - - -\n$(X)"; \
	fi
	@echo "$(DARK_MAGENTA)- - - - - 📦 MLX42 NOT cloned 📦 - - - - - -\n$(X)";

mlx42: clone_mlx42
	cmake $(MLX42_DIR) -B $(MLX42_DIR)build/ && make -C $(MLX42_DIR)build/
	@echo "$(DARK_MAGENTA)- - - - -✨📦 MLX42 compiled 📦✨- - - - - -\n$(X)"

clean:
	@clear
	@rm -rf $(OBJS_DIR)
	@rm -rf $(MLX42_DIR)build/
	@make -C ./libs/libft/ clean
	@echo "$(DARK_MAGENTA)- - - - -❗All object files cleaned❗- - - - -$(X)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "$(DARK_MAGENTA)- - - -❗All executable files cleaned❗- - - -$(X)"

re: fclean all
	@echo "$(DARK_MAGENTA)Sucessfully cleaned and rebuilt everything$(X)"