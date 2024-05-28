NAME = cub3d

SRC = $(shell find ./src -name "*.c")
OBJ_DIR = ./obj
OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)

LIBMLX	:= ./submodules/MLX42
LIBFT	:= ./submodules/42_libft
GNL		:= ./lib/get_next_line

GLFW_PATH := $(shell brew --prefix glfw)

HEADERS := -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include -I $(GNL)/include -I $(GLFW_PATH)/include
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -L$(GLFW_PATH)/lib -lglfw $(LIBFT)/libft.a $(GNL)/libftgnl.a
CFLAGS := -Wall -Werror -Wextra -Wunreachable-code -g

$(NAME): setup $(OBJ) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a $(GNL)/libftgnl.a
	cc $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	cc $(CFLAGS) -o $@ -c $< $(HEADERS)

all: libmlx libft gnl $(NAME)
clean:
	rm -rf $(OBJ_DIR)
	@if [ -d "$(LIBFT)" ]; then make -C $(LIBFT) clean; fi
	@if [ -d "$(GNL)" ]; then make -C $(GNL) clean; fi
fclean: clean
	rm -rf $(LIBMLX)/build
	@if [ -d "$(LIBFT)" ]; then make -C $(LIBFT) fclean; fi
	@if [ -d "$(GNL)" ]; then make -C $(GNL) fclean; fi
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
	@if [ ! -d "$(LIBMLX)" ] || [ ! -d "$(LIBFT)" ]; then \
		git submodule update --remote --init --recursive; \
	fi

debug: CFLAGS += -g -O0
debug: fclean all

random: all
	$(NAME) $(find ./assets/maps -type f -name '*.cub' | sort -R | head -n 1)

.PHONY: all clean fclean re setup libmlx libft gnl
