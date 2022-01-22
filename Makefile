
all:
	gcc -I libft/ -I source/  -I minilibx/ -I get_next_line/ libft/*.c source/*.c get_next_line/*.c /home/aregenia/Project/FdF/minilibx/libmlx.a -Imlx -lXext -lX11 -lm -lz -o fdf
	./fdf test_maps/42.fdf