NAME = cub3d

SRC = $(shell find ./src -name "*.c")
OBJ_DIR = ./obj
OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)

LIBMLX	:= ./submodules/MLX42
LIBFT	:= ./submodules/42_libft
GNL		:= ./submodules/42_get_next_line

HEADERS := -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include -I $(GNL)/include
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw $(LIBFT)/libft.a $(GNL)/libftgnl.a
CFLAGS := -Wall -Werror -Wextra -Wunreachable-code -g #-fsanitize=address

$(NAME): $(OBJ) $(LIBMLX)/build/libmlx42.a
	cc $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -o $@ -c $< $(HEADERS)

all: libmlx $(NAME)
clean:
	rm -rf $(OBJ_DIR)
fclean: clean
	rm -rf $(LIBMLX)/build
	rm -f $(NAME)
re: fclean all

$(LIBMLX)/build/libmlx42.a:
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4
libmlx: $(LIBMLX)/build/libmlx42.a

$(LIBFT)/libft.a:
	make -C $(LIBFT)
libft: $(LIBFT)/libft.a

$(GNL)/libftgnl.a:
	make -C $(GNL)
gnl: $(GNL)/libftgnl.a

.PHONY: all clean fclean re libmlx libft gnl
