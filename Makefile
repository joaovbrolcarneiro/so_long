# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = mlx

# Files
NAME = so_long
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# MLX Flags and Includes
INCLUDES = -I/usr/include -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(MLX_DIR)  # Build MLX library
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

bonus: CFLAGS += -DBONUS
bonus: all

clean:
	@make clean -C $(MLX_DIR)  # Clean MLX library
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

