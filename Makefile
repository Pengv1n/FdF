NAME := fdf

TEST_FILE := test_maps/42.fdf

cc := gcc
FLAGS := -Wall -Werror -Wextra
MINILIBX_FLAGS := -Imlx -lXext -lX11 -lm -lz

MINILIBX_DIR := minilibx
MINILIBX_LIB := $(MINILIBX_DIR)/libmlx.a

LIBFT_DIR := libft
LIBFT := libft.a

GNL_DIR := get_next_line
GNL_SRC := $(GNL_DIR)/get_next_line.c
GNL_HEAD := $(GNL_DIR)/get_next_line.h

SRC_DIR := source
HEAD := fdf.h
SRC := 	$(SRC_DIR)/calc_proj.c \
		$(SRC_DIR)/calculation.c \
		$(SRC_DIR)/center.c \
		$(SRC_DIR)/color.c \
		$(SRC_DIR)/disp.c \
		$(SRC_DIR)/disp_utils.c \
		$(SRC_DIR)/free.c \
		$(SRC_DIR)/ft_utils.c \
		$(SRC_DIR)/gradient.c \
		$(SRC_DIR)/hook.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/rotate.c \
		$(SRC_DIR)/shift.c \
		$(SRC_DIR)/zoom.c \
		$(GNL_SRC)

OBJ := $(SRC:.c=.o)

INCLUDES := -I $(LIBFT_DIR) $(SRC_DIR) $(GNL_DIR)

RM := rm -f

$(NAME):	$(OBJ) $(SRC)
		make -C $(LIBFT_DIR)/ all
		$(CC) -o $(NAME) $(OBJ) $(LIBFT_DIR)/$(LIBFT) $(MINILIBX_LIB) $(FLAGS) $(MINILIBX_FLAGS)

.o:		.c $(HEAD) $(GNL_HEAD) Makefile
		$(CC) $(FLAGS) (MINILIBX_FLAGS) $(INCLUDES) -o $@ -c $<

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:
	fclean all

test: all
	./$(NAME) $(TEST_FILE)

.PHONY: all clean fclean re