NAME = cub3D
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./libs/mlx
MLX_LIB = $(MLX_DIR)/libmlx42.a
GNL_DIR = ./libs/getnextline/
MOVE_DIR = ./src/player_move/
CHECK_DIR = ./src/checks/
PARSER_DIR = ./src/parser/
MINIMAP_DIR = ./src/minimap/
RAY_DIR = ./src/raycasting/
HOOK_DIR = ./src/hooks/
FLAGS = -Wall -Werror -Wextra -g 
LFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
INC = -I ./includes -I $(MLX_DIR)/include -I $(LIBFT_DIR) -I $(GNL_DIR)
SRC =	./src/main.c \
	 	./src/minimap/minimap.c \
	 	$(PARSER_DIR)set_dir.c \
		$(PARSER_DIR)get_colors.c \
		$(PARSER_DIR)get_textures.c \
		$(PARSER_DIR)open_file.c \
		$(PARSER_DIR)parse_data.c \
		$(PARSER_DIR)parse_map.c \
		$(CHECK_DIR)cardinal_check.c \
		$(CHECK_DIR)char_check.c \
		$(CHECK_DIR)map_check.c \
		$(CHECK_DIR)walls_check.c \
		$(GNL_DIR)get_next_line.c \
		$(GNL_DIR)get_next_line_utils.c \
		$(RAY_DIR)display.c \
		$(RAY_DIR)raycast.c \
		$(RAY_DIR)ray.c \
		$(RAY_DIR)set_texture.c \
		$(HOOK_DIR)hooks.c \
		$(HOOK_DIR)strafe.c \
		$(HOOK_DIR)mouse_hook.c \
		$(HOOK_DIR)key_hook.c \
		./src/printDELETEWHENFINISHED/printstuff.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)
$(NAME): $(MLX_LIB) $(LIBFT) $(OBJ)
	gcc  $(OBJ) $(INC) $(MLX_LIB) -lglfw3 $(LIBFT) $(LFLAGS) -o $(NAME) 

%.o: %.c
	gcc  $(INC) $(FLAGS) -c $< -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)
	cd $(MLX_DIR) && cp ./libmlx42.a ../../

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(OBJ) $(OBJ_BONUS) libmlx42.a

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all
.PHONY: all clean fclean re bonus