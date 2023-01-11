NAME = cub3D
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./libs/mlx
MLX_LIB = $(MLX_DIR)/libmlx42.a
FLAGS = -Wall -Werror -Wextra -g 
LFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
INC = -I ./includes -I $(MLX_DIR)/include -I $(LIBFT_DIR)
SRC = ./src/main.c

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