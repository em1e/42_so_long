# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 11:14:33 by vkettune          #+#    #+#              #
#    Updated: 2024/03/25 10:17:25 by vkettune         ###   ########.fr        #
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

# Debugging
DEBUG_NAME = debug.out
DEBUG_FLAGS = $(CFLAGS) -g -fsanitize=address,undefined,integer
DEBUG_OBJ_DIR = objs/debug_objs/

$(DEBUG_OBJ_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(DEBUG_OBJ_DIR)$(subst $(SRCS_DIR),,$(dir $<))
	@echo Building debug $<
	@$(CC) $(DEBUG_FLAGS) -c $< -o $@
 
$(DEBUG_NAME): $(DEBUG_OBJS)
	@echo Compiling debug executable
	@$(CC) $(DEBUG_FLAGS) $(DEBUG_OBJS) -o $@
	@echo Debug done

# Libraries
LIBFT = ./libs/libft/libft.a
MLX42 = $(MLX42_DIR)build/libmlx42.a

LIBFT_OBJ = ./libs/libft/objs/
MLX42_DIR = ./libs/MLX42/

# LIBS = $(LIBFT) $(MLX42) $(DEPEND)
LIBS = $(LIBFT) $(MLX42) -Iinclude -lglfw \
		-L"/Users/$(USER)/.brew/opt/glfw/lib/"

SRCS_DIR = srcs/
OBJS_DIR = objs/

# fetch.c
FILES = free.c errors.c game.c grid.c \
 main.c map.c get.c images.c move_player.c 
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

debug: debug.out

folders:
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(LIBFT_OBJ)
	@echo "$(DARK_MAGENTA)- - - - - 📁 Created all folders! 📁 - - - - -\n$(X)"

clone_mlx42:
	if [ ! -d "$(MLX42_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
		echo "$(DARK_MAGENTA)- - - - - - 📦 MLX42 cloned! 📦 - - - - - -\n$(DEF_COLOR)"; \
	fi
	@echo "$(DARK_MAGENTA)- - - - - 📦 MLX42 NOT cloned 📦 - - - - - -\n$(X)";

mlx42: clone_mlx42
	cmake $(MLX42_DIR) -B $(MLX42_DIR)build/ && make -C $(MLX42_DIR)build/
	@echo "$(DARK_MAGENTA)- - - - -✨📦 MLX42 compiled 📦✨- - - - - -\n$(X)"

libft:
	@make -C ./libs/libft

clean:
	@clear
	@rm -rf $(OBJS_DIR)
	@rm -rf $(MLX42_DIR)build/
	@make -C ./libs/libft/ clean
	@echo "$(DARK_MAGENTA)- - - - -❗All object files cleaned❗- - - - -$(X)"

fclean: clean
	@rm -f $(NAME) $(DEBUG_NAME)
	@rm -f $(LIBFT)
	@echo "$(DARK_MAGENTA)- - - -❗All executable files cleaned❗- - - -$(X)"

re: fclean all
	@echo "$(DARK_MAGENTA)Sucessfully cleaned and rebuilt everything$(X)"