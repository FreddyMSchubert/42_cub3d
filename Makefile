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

$(NAME): $(OBJ) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a $(GNL)/libftgnl.a
	cc $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	cc $(CFLAGS) -o $@ -c $< $(HEADERS)

all: libmlx libft gnl $(NAME)
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT) clean
	make -C $(GNL) clean
fclean: clean
	rm -rf $(LIBMLX)/build
	make -C $(LIBFT) fclean
	make -C $(GNL) fclean
	rm -f $(NAME)
re: fclean all

$(LIBMLX)/build/libmlx42.a: | setup
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4
libmlx: $(LIBMLX)/build/libmlx42.a

$(LIBFT)/libft.a: | setup
	make -C $(LIBFT)
	make -C $(LIBFT) bonus
	make -C $(LIBFT) xtra
libft: $(LIBFT)/libft.a

$(GNL)/libftgnl.a: | setup
	make -C $(GNL)
gnl: $(GNL)/libftgnl.a

setup:
	git submodule update --remote --init --recursive

.PHONY: all clean fclean re setup libmlx libft gnl
