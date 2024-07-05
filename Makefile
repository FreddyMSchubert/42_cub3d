NAME = cub3d

SRC = $(shell find ./src -name "*.c")
OBJ_DIR = ./obj
OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)

LIBMLX	:= ./submodules/MLX42
LIBFT	:= ./submodules/42_libft
GNL		:= ./lib/get_next_line

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	GLFW_PATH := $(shell pkg-config --variable=prefix glfw3)
endif
ifeq ($(UNAME_S),Darwin)
	GLFW_PATH := $(shell brew --prefix glfw)
endif

HEADERS := -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include -I $(GNL)/include -I $(GLFW_PATH)/include
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lm -L$(GLFW_PATH)/lib -lglfw $(LIBFT)/libft.a $(GNL)/libftgnl.a
CFLAGS := -Wall -Werror -Wextra -Ofast -march=native -flto -funroll-loops

$(NAME): setup $(OBJ) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a $(GNL)/libftgnl.a
	cc $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	cc $(CFLAGS) -o $@ -c $< $(HEADERS) -g

all: setup libmlx libft gnl $(NAME)
	rm -f save.cubsave
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
	@if [ -z "$(shell ls -A $(LIBMLX) 2>/dev/null)" ] || [ -z "$(shell ls -A $(LIBFT) 2>/dev/null)" ]; then \
		echo "Submodules appear empty or not cloned. Initializing and updating submodules..."; \
		git submodule update --init --recursive; \
	else \
		echo "Submodules are initialized. 🦦"; \
	fi


# ifeq ($(UNAME_S),Linux)
# 	debug: CFLAGS += -g -O0
# 	debug: fclean all
# endif
# ifeq ($(UNAME_S),Darwin)
# 	debug: CFLAGS += -fsanitize=address -g -O0
# 	debug: fclean all
# endif

debug: CFLAGS += -g -O0
debug: fclean all

random: all
	./random_map.sh

norm:
	norminette ./include
	norminette ./src
	make 

.PHONY: all clean fclean re setup libmlx libft gnl
